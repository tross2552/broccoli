#include "brclpch.h"
#include "Collision.h"

namespace brcl {
	
	typedef bool (PhysicsShape::* IntersectTest)(PhysicsShape& other);
	std::unordered_map<std::uint64_t, IntersectTest> PhysicsShape::collisionCases;
	
	const std::uint32_t PhysicsCircle::collid = typeid(PhysicsCircle).hash_code();
	const std::uint32_t PhysicsAABB::collid = typeid(PhysicsAABB).hash_code();
	
	bool intersectCircles(PhysicsCircle circle1, PhysicsCircle circle2)
	{
		const Vector2 diff = circle2.center - circle1.center;
		const float radii_sum = circle1.radius + circle2.radius;

		return Dot(diff, diff) < radii_sum * radii_sum;
	}

	bool intersectAABBs(PhysicsAABB box1, PhysicsAABB box2)
	{
		for (int i = 0; i < 2; ++i)
			if (box1.max[i] < box2.min[i] || box1.min[i] > box2.max[i]) return false;
		
		return true;
	}

	bool intersectCircleAABB(PhysicsAABB box, PhysicsCircle circle)
	{
		Vector2 q = circle.center;
		for(int i = 0; i < 2; ++i)
		{
			if (q[i] < box.min[i]) q[i] = box.min[i];
			if (q[i] > box.max[i]) q[i] = box.max[i];
		}

		q -= circle.center;
		return Dot(q, q) < circle.radius * circle.radius;
	}

	void PhysicsCircle::Translate(Vector2 offset)
	{
		center += offset;
	}

	bool PhysicsCircle::IntersectAABB(PhysicsAABB other)
	{
		return intersectCircleAABB(other, *this);
	}

	bool PhysicsCircle::IntersectCircle(PhysicsCircle other)
	{
		return intersectCircles(*this, other);
	}

	void PhysicsAABB::Translate(Vector2 offset)
	{
		min += offset;
		max += offset;
	}

	bool PhysicsAABB::IntersectAABB(PhysicsAABB other)
	{
		return intersectAABBs(*this, other);
	}

	bool PhysicsAABB::IntersectCircle(PhysicsCircle other)
	{
		return intersectCircleAABB(*this, other);
	}

	bool PhysicsShape::checkCollision(PhysicsShape& other)
	{
		auto handler = collisionCases.find(key(tid, other.tid));
		if (handler != collisionCases.end())
		{
			return (this->*handler->second)(other); // pointer-to-method call
		}
		else
		{
			BRCL_CORE_ERROR("Physics Error: Couldn't find intersection test for {0}, {1}", tid, other.tid);
			// default collision handling
			return false;
		}
	}

	void PhysicsCircle::InitCases()
	{
		addHandler(collid, collid, IntersectTest(&PhysicsCircle::IntersectCircle));
		addHandler(collid, PhysicsAABB::GetCollID(), IntersectTest(&PhysicsCircle::IntersectAABB));
	}

	void PhysicsAABB::initCases()
	{
		addHandler(collid, PhysicsCircle::GetCollID(), IntersectTest(&PhysicsAABB::IntersectCircle));
		addHandler(collid, collid, IntersectTest(&PhysicsAABB::IntersectAABB));
	}

}
