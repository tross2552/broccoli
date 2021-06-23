#include "brclpch.h"
#include "Camera.h"

#include "blaze/Blaze.h"
#include "Broccoli/Math/Math.h"

namespace brcl
{
	//TODO: implement perspective camera
	Camera::Camera(float left, float right, float bottom, float top) :
		m_Orthographic(true), m_ProjectionMatrix(Ortho(left,right,bottom,top)) {}

	void Camera::CalculateViewMatrix()
	{
		
	}
}
