#pragma once

#include "Broccoli/Math/Math.h"

namespace brcl
{
	class Camera
	{
	public:

		Camera(float left, float right, float bottom, float top);

		void OnUpdate();

		void SetPosition(const Vector3& position) { m_Position = position; }
		const Vector3& GetPosition() const { return m_Position; }

		void SetRotation(const Vector3& rotation) { m_Rotation = rotation; }
		const Vector3& GetRotation() const { return m_Rotation; }
		
		void SetProjectionMatrix(const Matrix4x4& proj) { m_ProjectionMatrix = proj; }
		Matrix4x4 GetProjectionMatrix() const { return m_ProjectionMatrix; };
		
		void SetViewMatrix(const Matrix4x4& view) { m_ViewMatrix = view; }
		Matrix4x4 GetViewMatrix() const { return m_ViewMatrix; };

		Matrix4x4 GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; };

		void SetOrthographic(bool orthographic) { m_Orthographic = orthographic; }
		bool IsOrthographic() const { return m_Orthographic; }

	protected:

		bool m_Orthographic;

		Vector3 m_Position;
		Vector3 m_Rotation;
		
		Matrix4x4 m_ProjectionMatrix;
		Matrix4x4 m_ViewMatrix;
		Matrix4x4 m_ViewProjectionMatrix;

	private:

		void CalculateViewMatrix();
		
		
	};

}