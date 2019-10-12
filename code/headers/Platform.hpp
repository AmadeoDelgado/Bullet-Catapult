#pragma once
#include "Actor.hpp"

class Platform {

	shared_ptr< btRigidBody > platform;
	float speed{ 1.f };
	btVector3 direction { 0, 0, 0 };

public:

	Platform(Scene * Scene, btVector3 position, shared_ptr<btDiscreteDynamicsWorld> world, btVector3 direction, float speed, size_t id);
	void ActivatePlatform();
	void DeactivatePlatform();
	///Returns true if index is equal to the rigidbody of the platform
	inline bool collided(size_t index) { if (platform->getWorldArrayIndex() == index) return true; return false; }



};