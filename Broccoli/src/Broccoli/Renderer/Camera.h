#pragma once

#include "Broccoli/Transform.h"
#include "Broccoli/Math/Math.h"

namespace brcl
{
	class Camera
	{
	public:

		Camera(float aspectRatio) :
			m_ProjectionMatrix(Ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f)) {}
		
		Camera(float left, float right, float bottom, float top) :
			m_ProjectionMatrix(Ortho(left, right, bottom, top)) {}
		
		Camera(const Matrix4x4& projection) :
			m_ProjectionMatrix(projection) {}

		void ChangeAspectRatio(float aspectRatio)
		{
			m_ProjectionMatrix = Ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f);
		}
		void SetProjectionMatrix(float left, float right, float bottom, float top)
		{
			m_ProjectionMatrix = Ortho(left, right, bottom, top);
		}
		
		void SetProjectionMatrix(const Matrix4x4& mat) { m_ProjectionMatrix = mat; }
		Matrix4x4 GetProjectionMatrix() const { return m_ProjectionMatrix; }

	protected:

		Matrix4x4 m_ProjectionMatrix;
		
		
	};

}