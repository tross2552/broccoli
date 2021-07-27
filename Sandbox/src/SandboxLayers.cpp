#include "SandboxLayers.h"

#include "ScriptedEntities.h"
#include "imgui/imgui.h"

namespace Sandbox
{
	
	void SandboxLayer::OnAttach()
	{
		
		brcl::FrameBufferSpec fBufferSpec;
		fBufferSpec.Width = 1280;
		fBufferSpec.Height = 720;
		m_Framebuffer = brcl::Framebuffer::Create(fBufferSpec);

		m_Scene = std::make_shared<brcl::Scene>();

		m_Level = m_Scene->CreateEntity("Level");
		m_Level.AddComponent<brcl::ScriptComponent>().Bind<Level>();

		m_Player = m_Scene->CreateEntity("Player");
		m_Player.AddComponent<brcl::CameraComponent>(16.0f / 9.0f);
		m_Player.AddComponent<brcl::ScriptComponent>().Bind<Player>();

		m_Scene->OnPlay();

		m_AspectRatio = (float)fBufferSpec.Width / fBufferSpec.Height;
		
	}

	void SandboxLayer::OnDetach()
	{
	}

	void SandboxLayer::OnUpdate(brcl::Timestep deltaTime)
	{
		BRCL_TRACE("Sandbox: Update ({0}) ", deltaTime.ToString());
		
		//m_Framebuffer->Bind();

		brcl::renderer2d::ResetStats();
		m_Scene->OnUpdate(deltaTime);

		//m_Framebuffer->Unbind();
		
	}

	bool SandboxLayer::OnResize(brcl::WindowResizedEvent& event) //todo: move this back into the engine
	{
		m_Scene->OnViewportResize(event.GetWidth(), event.GetHeight());
		return false;
	}

	void SandboxLayer::OnEvent(brcl::Event& event)
	{
		BRCL_TRACE("{0}", event);
		brcl::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<brcl::WindowResizedEvent>(BRCL_BIND_EVENT_FN(SandboxLayer::OnResize));
		
	}

	//--------------Engine Debug Application-----------------
	
	void ExampleImGuiLayer::OnImGuiRender()
	{
		static auto renderdebug = brcl::renderer2d::GetStats();
		renderdebug = brcl::renderer2d::GetStats();
		
		ImGui::Begin("Renderer Stats");
		ImGui::Text("Draw Calls: %d", renderdebug.DrawCalls);
		ImGui::Text("Quads: %d", renderdebug.QuadCount);
		ImGui::Text("Vertices: %d", renderdebug.GetTotalVertexCount());
		ImGui::Text("Indices: %d", renderdebug.GetTotalIndexCount());
		ImGui::End();
	}

	void ExampleImGuiLayer::OnEvent(brcl::Event& event)
	{

	}
}