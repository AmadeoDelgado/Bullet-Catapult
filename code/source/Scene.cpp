#include "Scene.hpp"
#include <iostream>

///Sets the camera aspect ratio
 void Scene::reset_viewport(const sf::Window & window)
{
	GLsizei width = GLsizei(window.getSize().x);
	GLsizei height = GLsizei(window.getSize().y);

	scene->get_active_camera()->set_aspect_ratio(float(width) / height);

	glViewport(0, 0, width, height);
}

 ///Initial ajustments
void Scene::initialize_scene()
{

	scene->get("light")->translate(Vector3(10.f, 10.f, 10.f));
	scene->get("camera")->translate(Vector3(-0.f, 5.f, 15.f));

}


///updates the transform of the mesh 
 void Scene::update()
{
	for (auto node : nodes)
	{
		node.second->getMotionState()->getWorldTransform(physics_transform);
		physics_transform.getOpenGLMatrix(glm::value_ptr(graphics_transform));

		node.first->set_transformation(graphics_transform);
	}
	
	
}



Scene::Scene()
{
	shared_ptr< Camera      > camera(new Camera(20.f, 1.f, 50.f, 1.f));
	shared_ptr< Light       > light(new Light);
	scene->add("camera", camera);
	scene->add("light", light);

}

Scene::~Scene()
{
	nodes.clear();
	rigidBodies.clear();
	motionStates.clear();
	collisionShapes.clear();
}