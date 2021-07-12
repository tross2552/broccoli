#pragma once
#include "Math/Math.h"

namespace brcl
{
	class Transform
	{
	public:

		Transform();
		
		Matrix4x4 GetMatrix() const;

		void AbsMove(const Vector3& distance) { m_Position += distance; }

		void SetPosition(const Vector3& position) { m_Position = position; }
		const Vector3& GetPosition() const { return m_Position; }

		void SetRotation(const Vector3& rotation) { m_Rotation = rotation; }
		const Vector3& GetRotation() const { return m_Rotation; }

		void SetScale(float scale) { m_Scale = Vector3(scale); }
		void SetScale(const Vector3& scale) { m_Scale = scale; }
		const Vector3& GetScale() const { return m_Scale; }

		

	
	private:

		Vector3 m_Position;
		Vector3 m_Rotation;
		Vector3 m_Scale;
	};

}
