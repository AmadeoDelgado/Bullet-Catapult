#include "Platform.hpp"
#include <math.h>
#include <string>
#include <iostream>

Platform::Platform(Scene * Scene, btVector3 position, shared_ptr<btDiscreteDynamicsWorld> world, btVector3 direction, float speed,size_t id) : speed(speed),direction(direction)
{

	Actor platActor(Scene);

	std::string name = "platform";
	name += id;
	std::cout << name << std::endl;
	platform = platActor.add_Dynamic_cube(btVector3(4.f, 0.5f, 15.f), position, world, "../../assets/platform.obj",name.c_str());
	platform->setLinearFactor(btVector3(std::abs(direction.getX()), std::abs(direction.getY()), std::abs(direction.getZ()) ));
	platform->setAngularFactor(btVector3{ 0.0f, 0.0f, 0.0f });
	platform->setMassProps(10000, btVector3(0, 0, 0));

}

///Moves plataform in the direction set
void Platform::ActivatePlatform()
{
	platform->setLinearVelocity(direction*speed);
}

///Moves plataform in the opossite direction set
void Platform::DeactivatePlatform()
{
	platform->setLinearVelocity(direction*-speed);
}
