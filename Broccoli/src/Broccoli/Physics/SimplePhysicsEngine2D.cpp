#include "brclpch.h"
#include "SimplePhysicsEngine2D.h"
#include "Broccoli/Scene/Scene.h"

namespace brcl
{
	PhysicsDebugStats2D SimplePhysicsEngine2D::stats = { 0,0,0, false };
	PhysicsWorld SimplePhysicsEngine2D::m_PhysicsWorld;
	std::unordered_map<entt::entity, Collidable*> SimplePhysicsEngine2D::m_Collidables;
	std::unordered_map<entt::entity, RigidBody*>  SimplePhysicsEngine2D::m_Bodies;
	
	
	void SimplePhysicsEngine2D::Init()
	{
		PhysicsCircle::InitCases();
		PhysicsAABB::initCases();

		m_Collidables.reserve(20);
		m_Bodies.reserve(20);
	}

	void SimplePhysicsEngine2D::Update(float deltaTime)
	{
		
		//simulate
		for (auto& rb : m_PhysicsWorld.GetRigidBodies())
		{
			if (rb.simType == RigidBody::SimulationType::Dynamic)
			{
				rb.Translate(rb.velocity * deltaTime);
			}
		}
		//collision detection

		auto compareTo = m_PhysicsWorld.GetCollidables();
		
		stats.Collisions = 0;
		
		for (auto it = compareTo.begin(); it != compareTo.end(); ++it)
		{
			
			for (auto it2 = it + 1; it2 != compareTo.end(); ++it2)
			{
				if(it->shape->checkCollision(*it2->shape)) stats.Collisions++;
			}
		}
		//resolve collisions

		//update gameobject transforms
		auto scene = Scene::GetActiveScene();
		for(auto& body : m_Bodies)
		{
			auto pos = Vector3{ body.second->position[0], body.second->position[1], 0 };
			scene->SetTransform(body.first, pos);
		}
		
	}

	void SimplePhysicsEngine2D::CreateCollider(entt::entity entity, CircleColliderComponent circle)
	{
		auto collidable = m_PhysicsWorld.AddCircle(circle.position, circle.radius);
		m_Collidables.emplace(std::pair(entity, &collidable));
		stats.Circles++;
	}
	
	void SimplePhysicsEngine2D::CreateCollider(entt::entity entity, BoxColliderComponent box)
	{
		auto& collidable = m_PhysicsWorld.AddAABB(box.position, box.position + box.size);
		m_Collidables.emplace(std::pair(entity, &collidable));
		stats.Boxes++;
	}

	void SimplePhysicsEngine2D::CreateRigidbody(entt::entity entity, RigidBodyComponent rb)
	{
		RigidBody::SimulationType simType;
		
		switch(rb.simType)
		{
		case RigidBodyComponent::SimulationType::Dynamic:
			simType = RigidBody::SimulationType::Dynamic;
			break;
		case RigidBodyComponent::SimulationType::Static:
			simType = RigidBody::SimulationType::Static;
			break;
		case RigidBodyComponent::SimulationType::Kinematic:
			simType = RigidBody::SimulationType::Kinematic;
			break;
		default:
			BRCL_CORE_WARN("Unknown rigid body simulation type: {0}", rb.simType);
			simType = RigidBody::SimulationType::Static;
		}

		Collidable* collidable = nullptr;
		if (auto it = m_Collidables.find(entity); it != m_Collidables.end()) collidable = it->second;
		
		auto& body = m_PhysicsWorld.AddRigidBody(rb.mass, collidable, simType);
		m_Bodies.emplace(std::pair(entity, &body));
		stats.RigidBodies++;
	}

	void SimplePhysicsEngine2D::ResetStats()
	{
		stats.RigidBodies = 0;
		stats.Circles = 0;
		stats.Boxes = 0;
		stats.Collisions = false;
	}

	void SimplePhysicsEngine2D::SetVelocity(entt::entity handle, Vector2 velocity)
	{
		if (auto it = m_Bodies.find(handle); it != m_Bodies.end()) 
			it->second->velocity = velocity;
	}
}
