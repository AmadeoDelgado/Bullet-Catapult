#include "Catapult.hpp"
#include <string>

///Creates and set up all bodies and hinges
Catapult::Catapult(Scene * Scene, btVector3 position, shared_ptr<btDiscreteDynamicsWorld> world, size_t id)
{
	Actor catapult(Scene);

	std::string body = "catapult_body"; 
	body += id;
	std::string fLeft = "fLeft";
	fLeft += id;
	std::string fright = "fright";
	fright += id;
	std::string bleft = "bleft";
	bleft += id;
	std::string bright = "bright";
	bright += id;
	std::string catapultArmname = "catapultArm";
	catapultArmname += id;
	std::string  proyectileName = "proyectile";
	proyectileName += id;

	//rigid bodies

	this->world = world.get();
	
	catapult_body = catapult.add_Dynamic_cube(btVector3(0.5f, 0.5f, 0.5f), btVector3(0.f, 3.f, 0.f) + position, world, "../../assets/catapultBody.obj",body.c_str());
	catapult_body->setLinearFactor(btVector3(1.0f, 1.f, 1.0f));
	catapult_body->setAngularFactor(btVector3(0.0f, 1.0f, 0.0f));
	catapult_body->setMassProps(10, catapult_body->getLocalInertia());

	
	f_l_wheel = catapult.add_Dynamic_sphere(1.f, btVector3(-1.f, 1.f, 1.f) + position, world, "../../assets/sphere.obj", fLeft.c_str());
	
	f_r_wheel = catapult.add_Dynamic_sphere(1.f, btVector3(-1.f, 1.f, -1.f) + position, world, "../../assets/sphere.obj", fright.c_str());
	
	b_l_wheel = catapult.add_Dynamic_sphere(1.f, btVector3(1.f, 1.f, 1.f) + position, world, "../../assets/sphere.obj", bleft.c_str());
	
	b_r_wheel = catapult.add_Dynamic_sphere(1.f, btVector3(1.f, 1.f, -1.f) + position, world, "../../assets/sphere.obj", bright.c_str());


	
	catapultArm = catapult.add_Dynamic_cube(btVector3(1.0f, 0.05f, 0.05f), btVector3(0.f, 4.f, 0.f) + position, world, "../../assets/catapultArm.obj", catapultArmname.c_str());

	
	proyectile = catapult.add_Dynamic_sphere(1.f, btVector3(200, 400, 0) + position, world, "../../assets/sphere.obj", proyectileName.c_str());
	proyectile->setMassProps(0.2, proyectile->getInvInertiaDiagLocal());

	//hinges

	btVector3 parentAxis(0.f, 1.f, 0.f);
	btVector3 childAxis(0.f, 0.f, 1.f);
	btVector3 anchor = catapult_body->getWorldTransform().getOrigin();
	
	f_l_hinge = new btHinge2Constraint(*catapult_body, *f_l_wheel, f_l_wheel->getWorldTransform().getOrigin(), parentAxis, childAxis);
	world->addConstraint(f_l_hinge, true);

	f_r_hinge = new btHinge2Constraint(*catapult_body, *f_r_wheel, f_r_wheel->getWorldTransform().getOrigin(), parentAxis, childAxis);
	world->addConstraint(f_r_hinge, true);

	b_l_hinge = new btHinge2Constraint(*catapult_body, *b_l_wheel, b_l_wheel->getWorldTransform().getOrigin(), parentAxis, childAxis);
	world->addConstraint(b_l_hinge, true);

	b_r_hinge = new btHinge2Constraint(*catapult_body, *b_r_wheel, b_r_wheel->getWorldTransform().getOrigin(), parentAxis, childAxis);
	world->addConstraint(b_r_hinge, true);


	arm_hinge = new btHingeConstraint(*catapult_body, *catapultArm, btVector3(0.0f, 2.f, 1.0f), btVector3(1.5f, 1.0f, 0.0f), childAxis, parentAxis);
	world->addConstraint(arm_hinge, true);
	arm_hinge->setLimit(1, 0.5);

	//Hinge adjustments

	f_r_hinge->setDamping(3, 0.5f);
	f_l_hinge->setDamping(3, 0.5f);
	b_r_hinge->setDamping(3, 0.5f);
	b_l_hinge->setDamping(3, 0.5f);

	f_r_hinge->enableMotor(3, true);
	f_r_hinge->setMaxMotorForce(3, 1000);
	f_r_hinge->setTargetVelocity(3, 0);

	f_l_hinge->enableMotor(3, true);
	f_l_hinge->setMaxMotorForce(3, 1000);
	f_l_hinge->setTargetVelocity(3, 0);

	b_r_hinge->enableMotor(3, true);
	b_r_hinge->setMaxMotorForce(3, 1000);
	b_r_hinge->setTargetVelocity(3, 0);

	b_l_hinge->enableMotor(3, true);
	b_l_hinge->setMaxMotorForce(3, 1000);
	b_l_hinge->setTargetVelocity(3, 0);
}

Catapult::~Catapult()
{


	delete f_r_hinge;
	delete f_l_hinge;
	delete b_l_hinge;
	delete b_r_hinge;
	delete arm_hinge;

	catapult_body.reset();
	f_l_wheel.reset();
	f_r_wheel.reset();
	b_l_wheel.reset();
	b_r_wheel.reset();
	catapultArm.reset();
	proyectile.reset();
}

void Catapult::clear_constraints()
{
	world->removeConstraint(f_r_hinge);
	world->removeConstraint(f_l_hinge);
	world->removeConstraint(b_l_hinge);
	world->removeConstraint(b_r_hinge);
	world->removeConstraint(arm_hinge);
}

void Catapult::move_foward()
{
	f_r_hinge->setTargetVelocity(3, speed);
	f_l_hinge->setTargetVelocity(3, speed);
	b_r_hinge->setTargetVelocity(3, speed);
	b_l_hinge->setTargetVelocity(3, speed);

}

void Catapult::move_backwards()
{
	f_r_hinge->setTargetVelocity(3, -speed);
	f_l_hinge->setTargetVelocity(3, -speed);
	b_r_hinge->setTargetVelocity(3, -speed);
	b_l_hinge->setTargetVelocity(3, -speed);

}

void Catapult::steer_left()
{
	f_r_hinge->setTargetVelocity(3, steeringSpeed);
	f_l_hinge->setTargetVelocity(3, -steeringSpeed);
	b_r_hinge->setTargetVelocity(3, steeringSpeed);
	b_l_hinge->setTargetVelocity(3, -steeringSpeed);

}

void Catapult::steer_right()
{
	f_r_hinge->setTargetVelocity(3, -steeringSpeed);
	f_l_hinge->setTargetVelocity(3, steeringSpeed);
	b_r_hinge->setTargetVelocity(3, -steeringSpeed);
	b_l_hinge->setTargetVelocity(3, steeringSpeed);

}

void Catapult::stop()
{
	f_r_hinge->setTargetVelocity(3, 0);
	f_l_hinge->setTargetVelocity(3, 0);
	b_r_hinge->setTargetVelocity(3, 0);
	b_l_hinge->setTargetVelocity(3, 0);
}

///Resets the proyectile position and adds force to the launcher
void Catapult::shoot()
{

	btTransform tr;

	catapultArm->getMotionState()->getWorldTransform(tr);
	proyectile->clearForces();
	proyectile->setWorldTransform(tr);
	proyectile->translate(btVector3(0, 2, 0));

	
	catapultArm->clearForces();
	catapultArm->applyCentralForce(btVector3(0.f, 700.f, 0.f));
}

float Catapult::getPosition()
{
	btTransform transform;
	catapult_body->getMotionState()->getWorldTransform(transform);
	return transform.getOrigin().getX();
}

///Returns true if the object is part of the catapult
bool Catapult::collided(size_t index)
{
	
	if (f_r_wheel->getWorldArrayIndex() == index ||
		f_l_wheel->getWorldArrayIndex() == index ||
		b_r_wheel->getWorldArrayIndex() == index ||
		b_l_wheel->getWorldArrayIndex() == index ||
		catapult_body->getWorldArrayIndex() == index||
		catapultArm->getWorldArrayIndex()   == index )
		
	{
		return true;
	};
		
	return false;
}
