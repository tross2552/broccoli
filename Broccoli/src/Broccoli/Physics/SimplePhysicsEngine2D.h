#pragma once
#include "entt.hpp"
#include "PhysicsWorld.h"
#include "Broccoli/Scene/Components.h"

namespace brcl {

	struct PhysicsDebugStats2D
	{
		unsigned int RigidBodies = 0;
		unsigned int Circles = 0;
		unsigned int Boxes = 0;
		unsigned int Collisions;
	};

	struct Collision2D
	{
		Vector2 normal;
		float penetration_depth;
	};
	
	class SimplePhysicsEngine2D
	{
	public: 

		static void Init();
		static void Update(float deltaTime);

		static void CreateCollider(entt::entity, CircleColliderComponent circle);
		static void CreateCollider(entt::entity, BoxColliderComponent box);
		static void CreateRigidbody(entt::entity, RigidBodyComponent rb);

		static PhysicsWorld& GetPhysicsWorld() { return m_PhysicsWorld; }

		static PhysicsDebugStats2D GetStats() { return stats; }
		static void ResetStats();

		static void SetVelocity(entt::entity handle, Vector2 velocity);


	private:
		
		static PhysicsWorld m_PhysicsWorld;
		
		static std::unordered_map<entt::entity, Collidable*> m_Collidables;
		static std::unordered_map<entt::entity, RigidBody*> m_Bodies;

		static PhysicsDebugStats2D stats;
	};

}