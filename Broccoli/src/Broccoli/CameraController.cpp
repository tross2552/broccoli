#include "brclpch.h"
#include "CameraController.h"
#include "Broccoli/Input.h"

namespace brcl
{
	CameraController::CameraController(float aspectRatio) :
		m_AspectRatio(aspectRatio), m_Camera(-aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{
	}

	void CameraController::OnUpdate(Timestep deltaTime)
	{

		bool rotateFlag = Input::IsKeyPressed(Input::BRCLKeyCodes::LEFT_SHIFT);

		if (Input::IsKeyPressed(Input::BRCLKeyCodes::W))
		{
			BRCL_CORE_INFO("UP UP UP UP !!!!!!!");
			if (!rotateFlag) m_Transform.SetPosition(m_Transform.GetPosition() + Vector3({ 0.0f, 1.0f, 0.0f }) * deltaTime);
			else m_Transform.SetRotation(m_Transform.GetRotation() + Vector3({ -1.0f,0.0f,0.0f }) * deltaTime);
		}

		if (Input::IsKeyPressed(Input::BRCLKeyCodes::A))
		{
			BRCL_CORE_INFO("LEFT LEFT LEFT LEFT !!!!!!!");
			if (!rotateFlag) m_Transform.SetPosition(m_Transform.GetPosition() + Vector3({ -1.0f, 0.0f, 0.0f }) * deltaTime);
			else m_Transform.SetRotation(m_Transform.GetRotation() + Vector3({ 0.0f,-1.0f,0.0f }) * deltaTime);
		}

		if (Input::IsKeyPressed(Input::BRCLKeyCodes::S))
		{
			BRCL_CORE_INFO("DOWN DOWN DOWN DOWN !!!!!!!");
			if (!rotateFlag) m_Transform.SetPosition(m_Transform.GetPosition() + Vector3({ 0.0f, -1.0f, 0.0f }) * deltaTime);
			else m_Transform.SetRotation(m_Transform.GetRotation() + Vector3({ 1.0f,0.0f,0.0f }) * deltaTime);
		}

		if (Input::IsKeyPressed(Input::BRCLKeyCodes::D))
		{
			BRCL_CORE_INFO("RIGHT RIGHT RIGHT RIGHT !!!!!!!");
			if (!rotateFlag) m_Transform.SetPosition(m_Transform.GetPosition() + Vector3({ 1.0f, 0.0f, 0.0f }) * deltaTime);
			else m_Transform.SetRotation(m_Transform.GetRotation() + Vector3({ 0.0f,1.0f,0.0f }) * deltaTime);
		}

		if (Input::IsKeyPressed(Input::BRCLKeyCodes::R))
		{
			if (!rotateFlag) m_Transform.SetPosition(m_Transform.GetPosition() + Vector3({ 0.0f, 0.0f, -1.0f }) * deltaTime);
			else m_Transform.SetRotation(m_Transform.GetRotation() + Vector3({ 0.0f,0.0f,-1.0f }) * deltaTime);
		}

		if (Input::IsKeyPressed(Input::BRCLKeyCodes::F))
		{
			if (!rotateFlag) m_Transform.SetPosition(m_Transform.GetPosition() + Vector3({ 0.0f, 0.0f, 1.0f }) * deltaTime);
			else m_Transform.SetRotation(m_Transform.GetRotation() + Vector3({ 0.0f,0.0f,1.0f }) * deltaTime);
		}

		if (Input::IsKeyPressed(Input::BRCLKeyCodes::X))
		{
			m_Transform.SetPosition({ 0.0f, 0.0f, 0.0f });
			m_Transform.SetRotation({ 0.0f,0.0f,0.0f });
			m_ZoomLevel = 1.0f;
		}

		m_Camera.SetViewMatrix(Invert(m_Transform.GetMatrix()));
		m_Camera.SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		m_Camera.UpdateVPMatrix();
		
	}

	void CameraController::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(BRCL_BIND_EVENT_FN(CameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizedEvent>(BRCL_BIND_EVENT_FN(CameraController::OnWindowResized));
	}

	bool CameraController::OnMouseScrolled(MouseScrolledEvent& event)
	{
		m_ZoomLevel -= event.GetYOffset() * 0.05f; //TODO: curve the controller's zoom
		m_ZoomLevel = std::max(0.05f, m_ZoomLevel);
		return false;
	}

	bool CameraController::OnWindowResized(WindowResizedEvent& event)
	{
		m_AspectRatio = static_cast<float>(event.GetWidth()) / event.GetHeight();
		return false;
	}
}
