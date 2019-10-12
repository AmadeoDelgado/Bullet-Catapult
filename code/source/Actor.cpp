#include "Actor.hpp"

  ///Consructor that initilizes the scene
	Actor::Actor(Scene * scene) : sceneRef(scene) {}

	///Creates model and adds it to the scene
	void Actor::add_model(const char * modelDir, const char * name)
	{
		shared_ptr< Model  > model(new Model_Obj(modelDir));
		sceneRef->scene->add(name, model);
	}


	///Adds a model and a cube dynamic rigid body 
	shared_ptr<btRigidBody> Actor::add_Dynamic_cube(btVector3 halfsize, btVector3 position, shared_ptr<btDiscreteDynamicsWorld> world, const char * modelDir, const char * name)
	{
		shared_ptr< btRigidBody > box_body;
		shared_ptr< btCollisionShape > shape(new btBoxShape(halfsize));


		// Create Dynamic Objects.

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(position);

		btScalar  mass = 1.f;
		btVector3 localInertia(0, 0, 0);

		shape->calculateLocalInertia(mass, localInertia);

		// Using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects

		shared_ptr< btDefaultMotionState >       state(new btDefaultMotionState(transform));
		btRigidBody::btRigidBodyConstructionInfo info(mass, state.get(), shape.get(), localInertia);

		box_body.reset(new btRigidBody(info));
		box_body->setActivationState(DISABLE_DEACTIVATION);
		box_body->setRestitution(0.1f);
		box_body->setFriction(7.1);
		world->addRigidBody(box_body.get());

		// Save the smart pointers for automatic cleanup.

		sceneRef->rigidBodies.push_back(box_body);
		sceneRef->motionStates.push_back(state);
		sceneRef->collisionShapes.push_back(shape);

		add_model(modelDir, name);

		sceneRef->nodes.emplace(sceneRef->scene->get(name), box_body);
		sceneRef->scene->get(name)->scale(0.5);
		return box_body;
	}

	///Adds a model and a sphere dynamic rigid body 
	shared_ptr<btRigidBody> Actor::add_Dynamic_sphere(float radius, btVector3 position, shared_ptr<btDiscreteDynamicsWorld> world, const char * modelDir, const char * name)
	{

		shared_ptr< btRigidBody > sphere_body;
		shared_ptr< btCollisionShape > shape(new btSphereShape(btScalar(radius)));

		// Create Dynamic Objects.

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(position);

		btScalar  mass = 1.f;
		btVector3 localInertia(0, 0, 0);

		shape->calculateLocalInertia(mass, localInertia);

		// Using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects

		shared_ptr< btDefaultMotionState >       state(new btDefaultMotionState(transform));
		btRigidBody::btRigidBodyConstructionInfo info(mass, state.get(), shape.get(), localInertia);

		sphere_body.reset(new btRigidBody(info));
		sphere_body->setActivationState(DISABLE_DEACTIVATION);
		sphere_body->setRestitution(0.1f);
		//sphere_body->setLinearFactor(btVector3(1, 0, 0));
		//sphere_body->setLinearVelocity(btVector3(-1, 0,0));
		world->addRigidBody(sphere_body.get());

		// Save the smart pointers for automatic cleanup.
		
		sceneRef->rigidBodies.push_back(sphere_body);
		sceneRef->motionStates.push_back(state);
		sceneRef->collisionShapes.push_back(shape);

		add_model(modelDir, name);

		sceneRef->nodes.emplace(sceneRef->scene->get(name), sphere_body);
		sceneRef->scene->get(name)->scale(0.5);
		return sphere_body;
	}

	///Adds a model and a cube static body 
	void Actor::add_Static_cube(btVector3 position, btVector3 halfsize, shared_ptr<btDiscreteDynamicsWorld> world, const char * modelDir, const char * name)
	{
		shared_ptr< btCollisionShape > shape(new btBoxShape(halfsize));

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(position);
		//transform.setRotation(btQuaternion(btVector3(0.0f,0.0f,1.0f),glm::radians(30.f)));

		// Using motionstate is optional for static objects.

		shared_ptr< btDefaultMotionState >       state(new btDefaultMotionState(transform));
		btRigidBody::btRigidBodyConstructionInfo info(0, state.get(), shape.get());
		shared_ptr< btRigidBody >                body(new btRigidBody(info));

		body->setRestitution(0.2f);
		body->setFriction(7.1f);
		//body->setLinearFactor(btVector3(0, 0, 0));

		// Add the body to the dynamics world.

		world->addRigidBody(body.get());

		// Save the smart pointers for automatic cleanup.


		sceneRef->rigidBodies.push_back(body);
		sceneRef->motionStates.push_back(state);
		sceneRef->collisionShapes.push_back(shape);

		add_model(modelDir, name);
		sceneRef->scene->get(name)->translate(Vector3(position.getX(), position.getY(), position.getZ()));
		//sceneRef->get(name)->

	}

	


	

	

