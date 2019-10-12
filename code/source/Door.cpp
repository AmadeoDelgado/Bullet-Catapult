#include "Door.hpp"
#include <string>

///Initialize the door 
Door::Door(Scene * Scene, btVector3 position, shared_ptr<btDiscreteDynamicsWorld> world, size_t id)
{
	Actor doorActor(Scene);
	std::string leftWall = "leftWall";
	leftWall += id;
	std::string rightWall = "rightWall";
	rightWall += id;
	std::string doorWall = "doorWall";
	doorWall += id;

	wall1 = doorActor.add_Dynamic_cube(btVector3(0.5f, 15.f, 5.f), btVector3(0.f, 30.f, 0.f) + position, world, "../../assets/wall1.obj", doorWall.c_str());
	wall1->setLinearFactor(btVector3(0.0f, 1.0f, 0.0f));
	wall1->setAngularFactor(btVector3(0.0f, 0.0f, 0.0f));

	wall2 = doorActor.add_Dynamic_cube(btVector3(0.5f, 15.f, 5.f), btVector3(0.f, 15.f, -10.f) + position, world, "../../assets/wall1.obj", rightWall.c_str());
	wall2->setLinearFactor(btVector3(0.0f, 0.0f, 0.0f));
	wall2->setAngularFactor(btVector3(0.0f, 0.0f, 0.0f));

	wall3 = doorActor.add_Dynamic_cube(btVector3(0.5f, 15.f, 5.f), btVector3(0.f, 15.f, 10.f) + position, world, "../../assets/wall1.obj", leftWall.c_str());
	wall3->setLinearFactor(btVector3(0.0f, 0.0f, 0.0f));
	wall3->setAngularFactor(btVector3(0.0f, 0.0f, 0.0f));



}


void Door::OpenDoor()
{
	wall1->setGravity(btVector3(0.0f, 10.0f, 0.0f));
}
