/*
    Bullet Continuous Collision Detection and Physics Library
    Copyright (c) 2003-2007 Erwin Coumans  http://continuousphysics.com/Bullet/

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it freely,
    subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
       If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.

    This is the official 'Hello, World' example cleaned up for additional simplicity and clarity.
*/

//#include <memory>
//#include <vector>
//#include <iostream>
//
//#include <Light.hpp>
//#include <Model.hpp>
//#include <OpenGL.hpp>
//#include <Model_Obj.hpp>
//#include <Render_Node.hpp>
//
//#include <SFML/Window.hpp>
//#include <btBulletDynamicsCommon.h>

#include "Scene.hpp"
#include "Door.hpp"
#include "Catapult.hpp"
#include "Platform.hpp"
#include "Key.hpp"
#include <iostream>

using namespace std;
using namespace glt;



int main ()
{
    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- +\
                                       PHYSISCS WORLD INITIALIZATION
    \+ -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- */

    // Collision configuration contains default setup for memory, collision setup.
    // Advanced users can create their own configuration.

    btDefaultCollisionConfiguration collisionConfiguration;

    // Use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded).

    btCollisionDispatcher collisionDispatcher(&collisionConfiguration);

    // btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.

    btDbvtBroadphase overlappingPairCache;

    // The default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded).

    btSequentialImpulseConstraintSolver constraintSolver;

    // Create and configure the physiscs world:

    shared_ptr< btDiscreteDynamicsWorld > dynamicsWorld
    (
        new btDiscreteDynamicsWorld
        (
            &collisionDispatcher,
            &overlappingPairCache,
            &constraintSolver,
            &collisionConfiguration
        )
    );

    dynamicsWorld->setGravity (btVector3(0, -10, 0));


    // Se crea la ventana y el contexto de OpenGL asociado a ella:

    sf::Window window
    (
        sf::VideoMode(1024, 720),
        "Práctica 2 animación: Amadeo Delgado Casado",
        sf::Style::Default,
        sf::ContextSettings(24, 0, 0, 3, 2, sf::ContextSettings::Core)      // Se usa OpenGL 3.2 core profile
    );

    // Se determinan las características de OpenGL disponibles en la máquina:

	if (!glt::initialize_opengl_extensions())
	{
		exit (-1);
	}

    // Se activa la sincronización vertical:

    window.setVerticalSyncEnabled (true);

    // Se crea y se configura la escena:

    
	Scene scene;
	scene.initialize_scene();

	

	

	//CAR

	Catapult catapult(&scene, btVector3(0, 0, 0), dynamicsWorld,1);
	catapult.setSpeed(4);
	catapult.setSteeringSpeed(3.5);
	

	//--------------------------------------

	//DOOR

	
	Door fdoor(&scene, btVector3(-7, 0, 0), dynamicsWorld,1);
	Key key(&scene, btVector3(3.f, 5.f, -3.f), dynamicsWorld, &fdoor,1);

	//------------------
	
	//platform


	Platform plat(&scene, btVector3(-19.f, 0.f, 0.f), dynamicsWorld, btVector3(-1.f, 0.f, 0.f), 1,1);
	
	

	//FLOOR

	Actor floor(&scene);
	shared_ptr< btRigidBody > target = floor.add_Dynamic_cube(btVector3(0.5f, 7.f, 7.f), btVector3(-59.f, 7.f, 0.f), dynamicsWorld, "../../assets/target.obj", "target");


	floor.add_Static_cube(btVector3(0.f, 0.f, 0.f), btVector3(15.f, 0.5f, 15.f), dynamicsWorld,"../../assets/floor1.obj","floor1");

	floor.add_Static_cube(btVector3(-60.f, 0.f, 0.f), btVector3(15.f, 0.5f, 15.f), dynamicsWorld, "../../assets/floor1.obj", "floor2");

	floor.add_Static_cube(btVector3(-55.f, 2.5f, 0.f), btVector3(1.f, 2.5f, 15.f), dynamicsWorld, "../../assets/blocking.obj", "floor3");

	

    // Se inicializan algunos elementos de OpenGL:

    //reset_viewport (window, *sceneRef);
	scene.reset_viewport(window);
    glClearColor (0.2f, 0.2f, 0.2f, 1.f);


    bool running = true;
    int  frame   = 0;

    do
    {

	
		//Follow catapult
		Matrix44 transform1 = scene.scene->get_active_camera()->get_transformation();
		transform1[3].x = catapult.getPosition();//transorm.getOrigin().getX();	
		scene.scene->get_active_camera()->set_transformation(transform1);
		
		//Colisiones
		int manifold_count = dynamicsWorld->getDispatcher()->getNumManifolds();
		for (int i = 0; i < manifold_count; i++)
		{
			btPersistentManifold * manifold =
				dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
			btCollisionObject * object_a = (btCollisionObject *)(manifold->getBody0());
			btCollisionObject * object_b = (btCollisionObject *)(manifold->getBody1());
			int numContacts = manifold->getNumContacts();
			for (int j = 0; j < numContacts; j++)
			{
				btManifoldPoint & point = manifold->getContactPoint(j);
				if (point.getDistance() < 0.f)
				{

					if (catapult.collided(object_a->getWorldArrayIndex()) && key.Collided(object_b->getWorldArrayIndex()) )
					{
						
						key.ActivateDoor();
						
					}

					if (catapult.collided(object_a->getWorldArrayIndex()) && plat.collided(object_b->getWorldArrayIndex()))
					{
						plat.ActivatePlatform();
					}
					
					
				}
			}
		}
        // Read the user input:

        sf::Event event;
		window.setKeyRepeatEnabled(false);
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				running = false;
				break;
				exit(1);
			}

			case sf::Event::Resized:
			{
				// reset_viewport (window, *sceneRef);
				scene.reset_viewport(window);
				break;
			}


			case sf::Event::KeyPressed:
			{
				//std::cout << "PRESS" << std::endl;
				if (event.key.code == sf::Keyboard::Space)
				{

					catapult.shoot();



				}


			}

			case sf::Event::KeyReleased:
			{




			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				
				catapult.move_foward();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				catapult.move_backwards();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				catapult.steer_left();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				catapult.steer_right();
			}
			
			else
			{
		
				catapult.stop();
			}
			
			}
		}

        // Perform the simulation:

        dynamicsWorld->stepSimulation (1.f / 60.f);

        // Apply the physics transform to the graphics model:

		scene.update();
		
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
		scene.scene->render();
		
        window.display ();
    }
    while (running);

    // Se debe destruir el mundo físico antes de que se destruyan los cuerpos rígidos:

	catapult.clear_constraints();

    dynamicsWorld.reset ();

    return EXIT_SUCCESS;
}
