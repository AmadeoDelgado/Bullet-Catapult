#pragma once
#include "Actor.hpp"

class Catapult {

	//Bodies

	shared_ptr< btRigidBody > catapult_body;
	shared_ptr< btRigidBody > f_l_wheel;
	shared_ptr< btRigidBody > f_r_wheel;
	shared_ptr< btRigidBody > b_l_wheel;
	shared_ptr< btRigidBody > b_r_wheel;
	shared_ptr< btRigidBody > catapultArm;
	shared_ptr< btRigidBody > proyectile;

	//Hinges

	btHinge2Constraint * f_l_hinge;
	btHinge2Constraint * f_r_hinge;
	btHinge2Constraint * b_l_hinge;
	btHinge2Constraint * b_r_hinge;

	btHingeConstraint * arm_hinge;
	
	float steeringSpeed = 1;
	float speed = 1;

	btDiscreteDynamicsWorld * world;

public:

	Catapult(Scene * Scene, btVector3 position, shared_ptr<btDiscreteDynamicsWorld> world,size_t id);

	///free all memory from constrains and then all rigidbodies
	~Catapult();
	///Removes all constraisn from world
	void clear_constraints();
	
	void move_foward();
	void move_backwards();
	void steer_left();
	void steer_right();
	void stop();
	void shoot();
	inline void setSpeed(float newspeed) { speed = newspeed; };
	inline void setSteeringSpeed(float newspeed) { steeringSpeed = newspeed; };
	float getPosition();
	bool collided(size_t index);


};