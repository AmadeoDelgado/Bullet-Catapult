#ifndef ACTOR_HEADER
#define  ACTOR_HEADER

#pragma once
#include "Scene.hpp"



	using namespace std;
	using namespace glt;

	class Actor
	{

		
		void add_model(const char * modelDir, const char * name);
	public:
		Actor(Scene * scene);
		Scene * sceneRef;
		shared_ptr< btRigidBody > add_Dynamic_cube(btVector3 halfsize, btVector3 position, shared_ptr< btDiscreteDynamicsWorld > world, const char * modelDir, const char * name);
		shared_ptr< btRigidBody > add_Dynamic_sphere(float radius, btVector3 position, shared_ptr< btDiscreteDynamicsWorld > world, const char * modelDir, const char * name);

		//Statics
		void add_Static_cube(btVector3 position, btVector3 halfsize, shared_ptr< btDiscreteDynamicsWorld > world, const char * modelDir, const char*name);





	};

#endif // !ACTOR_HEADER