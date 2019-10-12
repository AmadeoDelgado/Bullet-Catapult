#pragma once

#include <memory>
#include <vector>
#include <map>

#include <Light.hpp>
#include <Model.hpp>
#include <OpenGL.hpp>
#include <Model_Obj.hpp>
#include <Render_Node.hpp>

#include <SFML/Window.hpp>
#include <btBulletDynamicsCommon.h>

using namespace std;
using namespace	glt;

class Scene
{
public:

	//map of toolkit / bulletbodies
	map <Node*, shared_ptr< btRigidBody >> nodes;

	//vectors for buller
	vector< shared_ptr< btRigidBody          > > rigidBodies;
	vector< shared_ptr< btDefaultMotionState > > motionStates;
	vector< shared_ptr< btCollisionShape     > > collisionShapes;

	//variables for update
	btTransform physics_transform;
	glm::mat4 graphics_transform;

	//render
	shared_ptr< Render_Node > scene { new Render_Node };
    
	void reset_viewport(const sf::Window & window);
	void initialize_scene();
	
	void update();
	
	Scene();
	~Scene();

private:

};


