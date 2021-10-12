#pragma once
#include "Broccoli/Math/Math.h"
#include "Collision.h"

namespace brcl
{
	struct Collidable
	{
		Collidable(PhysicsShape* shape) :
			shape(shape) {}

		void Translate(Vector2 offset)
		{
			shape->Translate(offset);
		}
		
		PhysicsShape* shape;
	};

	struct RigidBody
	{
		enum class SimulationType
		{
			Dynamic,
			Static,
			Kinematic
		};

		
		RigidBody(float mass, Collidable* collidable, SimulationType simType, Vector2 velocity) :
			mass(mass), collidable(collidable), simType(simType), velocity(velocity) {}


		float mass;
		Collidable* collidable;
		SimulationType simType;
		Vector2 position;
		Vector2 velocity;

		void Translate(Vector2 offset)
		{
			if(collidable) collidable->Translate(offset);
			position += offset;
		}
	};

	class PhysicsWorld
	{
	public:

		PhysicsWorld();
		
		//collision layers
		//rigid bodies

		Collidable& AddCircle(Vector2 position, float radius);
		Collidable& AddAABB(Vector2 min, Vector2 max);
		
		RigidBody& AddRigidBody(float mass, Collidable* collidable, RigidBody::SimulationType simType);

		std::vector<Collidable>& GetCollidables() { return m_Collidables; }
		std::vector<RigidBody>& GetRigidBodies() { return m_RigidBodies; }
	
	private:
		
		std::vector<Collidable> m_Collidables;
		std::vector<RigidBody> m_RigidBodies;
		
		std::vector<PhysicsCircle> m_Circles;
		std::vector<PhysicsAABB> m_AABBs;
	};
}
