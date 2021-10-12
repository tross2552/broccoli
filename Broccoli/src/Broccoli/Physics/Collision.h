#pragma once
#include "Broccoli/Math/Math.h"
#include <Broccoli/Core/Log.h>

namespace brcl
{
	struct PhysicsAABB;
	struct PhysicsCircle;

	struct PhysicsShape
	{
		PhysicsShape(std::uint32_t collid) : tid(collid) {}

		virtual void Translate(Vector2 offset) = 0;
		
		typedef bool (PhysicsShape::*IntersectTest)(PhysicsShape& other);
		typedef std::unordered_map<std::uint64_t, IntersectTest> CollisionHandlerMap;

		bool checkCollision(PhysicsShape& other);

	protected:

		const std::uint32_t tid; // type id

		static void addHandler(std::uint32_t id1, std::uint32_t id2, IntersectTest handler)
		{
			collisionCases.insert(CollisionHandlerMap::value_type(key(id1, id2), handler));
		}
		static std::uint64_t key(std::uint32_t id1, std::uint32_t id2)
		{
			return std::uint64_t(id1) << 32 | id2;
		}

		static CollisionHandlerMap collisionCases;

	};

	struct PhysicsCircle : PhysicsShape
	{
		PhysicsCircle(Vector2 center, float radius) :
			PhysicsShape(collid), center(center), radius(radius) {}
		
		Vector2 center;
		float radius;

		void Translate(Vector2 offset) override;

		bool IntersectCircle(PhysicsCircle other);
		bool IntersectAABB(PhysicsAABB other);

		static std::uint32_t GetCollID() { return collid; }
		static void InitCases();

	private:
		static const std::uint32_t collid;
	};

	struct PhysicsAABB : PhysicsShape
	{
		PhysicsAABB(Vector2 min, Vector2 max) :
			PhysicsShape(collid), min(min), max(max) {}
		
		Vector2 min;
		Vector2 max;

		void Translate(Vector2 offset) override;

		bool IntersectCircle(PhysicsCircle other);
		bool IntersectAABB(PhysicsAABB other);

		static std::uint32_t GetCollID() { return collid; }
		static void initCases();
		
	
	private:
		static const std::uint32_t collid;
	};
}
