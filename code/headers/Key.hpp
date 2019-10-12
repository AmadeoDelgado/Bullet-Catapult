#pragma once
#include "Door.hpp"

class Key {

	shared_ptr< btRigidBody > key;
	Door * door;

public:
	Key(Scene * Scene, btVector3 position, shared_ptr<btDiscreteDynamicsWorld> world, Door * door, size_t id);
	///Calls open door of the referenced door
	inline void ActivateDoor() { door->OpenDoor(); key->translate(btVector3(-100, -100, -100)); };
	///Returns true if index is equal to the rigidbody of the key
	inline bool Collided(size_t index) { if (key->getWorldArrayIndex() == index)return true; return false; }

};