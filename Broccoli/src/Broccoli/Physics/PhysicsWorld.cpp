#include "brclpch.h"
#include "PhysicsWorld.h"

brcl::PhysicsWorld::PhysicsWorld()
{
	m_Collidables.reserve(20);
	m_AABBs.reserve(10);
	m_Circles.reserve(10);
	m_RigidBodies.reserve(20);
}

brcl::Collidable& brcl::PhysicsWorld::AddCircle(Vector2 position, float radius)
{
	auto circle = m_Circles.emplace_back(position, radius);
	return m_Collidables.emplace_back(&circle);
}

brcl::Collidable& brcl::PhysicsWorld::AddAABB(Vector2 min, Vector2 max)
{
	auto& box = m_AABBs.emplace_back(min, max);
	return m_Collidables.emplace_back(&box);
}

brcl::RigidBody& brcl::PhysicsWorld::AddRigidBody(float mass, Collidable* collidable, RigidBody::SimulationType simType)
{
	return m_RigidBodies.emplace_back(mass, collidable, simType, Vector2{0});
}
