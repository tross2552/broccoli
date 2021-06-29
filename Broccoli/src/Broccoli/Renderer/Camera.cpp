#include "brclpch.h"
#include "Camera.h"

#include "Broccoli/Math/Math.h"

namespace brcl
{
	//TODO: implement perspective camera
	Camera::Camera(float left, float right, float bottom, float top) :
		m_Orthographic(true), m_Position({ 0.0f,0.0f,0.0f }), m_Rotation({ 0.0f, 0.0f, 0.0f }), m_ProjectionMatrix(Ortho(left, right, bottom, top)), m_ViewMatrix(Identity4x4())
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::OnUpdate()
	{
		if(true) CalculateViewMatrix();
	}

	void Camera::CalculateViewMatrix()
	{
		Matrix4x4 view =Translate(Identity4x4(), m_Position);
		view = Rotate(view, m_Rotation);
		m_ViewMatrix = Invert(view);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
