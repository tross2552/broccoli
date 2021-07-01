#pragma once

#include "Broccoli/Transform.h"
#include "Broccoli/Math/Math.h"

namespace brcl
{
	class Camera
	{
	public:

		Camera(float left, float right, float bottom, float top);

		void OnUpdate();

		Transform& GetTransform() { return m_Transform; }
		
		void SetProjectionMatrix(const Matrix4x4& proj) { m_ProjectionMatrix = proj; }
		Matrix4x4 GetProjectionMatrix() const { return m_ProjectionMatrix; };
		
		void SetViewMatrix(const Matrix4x4& view) { m_ViewMatrix = view; }
		Matrix4x4 GetViewMatrix() const { return m_ViewMatrix; };

		Matrix4x4 GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; };

		void SetOrthographic(bool orthographic) { m_Orthographic = orthographic; }
		bool IsOrthographic() const { return m_Orthographic; }

	protected:

		Transform m_Transform;

		bool m_Orthographic;
		
		Matrix4x4 m_ProjectionMatrix;
		Matrix4x4 m_ViewMatrix;
		Matrix4x4 m_ViewProjectionMatrix;

	private:

		void CalculateViewMatrix();
		
		
	};

}