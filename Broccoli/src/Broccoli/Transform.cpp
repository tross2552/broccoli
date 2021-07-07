#include "brclpch.h"
#include "Transform.h"

namespace brcl
{
	Transform::Transform() :
		m_Position(0.0f), m_Rotation(0.0f), m_Scale(1.0f) {}

	Matrix4x4 Transform::GetMatrix() const
	{

		Matrix4x4 transform = Identity4x4();
		transform = Translate(transform, m_Position);
		transform = Rotate(transform, m_Rotation);
		transform = Scale(transform, m_Scale);

		return transform;
		
	}
}
