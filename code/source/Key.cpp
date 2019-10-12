#include "Key.hpp"
#include <string>

///Initialize the key
Key::Key(Scene * Scene, btVector3 position, shared_ptr<btDiscreteDynamicsWorld> world, Door * door,size_t id) : door(door)
{
	Actor keyActor(Scene);
	std::string name = "key";
	name += id;
	key = keyActor.add_Dynamic_sphere(1.f, position, world, "../../assets/key.obj",name.c_str() );

}