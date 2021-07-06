#include "brclpch.h"
#include "Camera.h"

#include "Broccoli/Math/Math.h"

namespace brcl
{
	//TODO: implement perspective camera
	Camera::Camera(float left, float right, float bottom, float top) :
		m_Orthographic(true), m_ProjectionMatrix(Ortho(left, right, bottom, top)), m_ViewMatrix(Identity4x4())
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::SetProjectionMatrix(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = Ortho(left, right, bottom, top);
	}

	void Camera::UpdateVPMatrix()
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
