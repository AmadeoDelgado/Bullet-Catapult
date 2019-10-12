#pragma once
#include "Actor.hpp"

class Door {

		shared_ptr< btRigidBody > wall1;
		shared_ptr< btRigidBody > wall2;
		shared_ptr< btRigidBody > wall3;

public:
	
	Door(Scene * Scene, btVector3 position, shared_ptr<btDiscreteDynamicsWorld> world,size_t id);
	void OpenDoor();



};