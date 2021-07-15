#include "EditorLayers.h"
#include "imgui/imgui.h"

namespace brcl
{
	
	void EditorLayer::OnAttach()
	{
		m_Texture = Texture2D::Create("assets/textures/broccoli_texture_small_formatted.png");

		FrameBufferSpec fBufferSpec;
		fBufferSpec.Width = 1280;
		fBufferSpec.Height = 720;
		m_Framebuffer = Framebuffer::Create(fBufferSpec);
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(Timestep deltaTime)
	{
		BRCL_TRACE("Editor: Update ({0}) ", deltaTime.ToString());
		if(m_Focused) m_CameraController.OnUpdate(deltaTime);

		m_Framebuffer->Bind();
		
		static float rotation = 0.0f;
		rotation += 0.01f;

		renderer2d::ResetStats();
		renderer2d::BeginScene(m_CameraController.GetCamera());
		Transform quad;
		Vector4 colorInv = 1.0f - m_Color;
		colorInv[3] = 1.0f;
		
		
		const int tiles = 20;
		const float tilescale = 0.5f;
		quad.SetScale(tilescale * 0.9f);
		for (int i = 0; i < tiles; i++)
		{
			for (int j = 0; j < tiles; j++)
			{
				quad.SetRotation({ sin(rotation) * j / (tiles), sin(rotation) * i / (tiles), sin(rotation) * (i+j) / (2*tiles) });
				quad.SetPosition(Vector3({ -(float)tiles/2 + i, -(float)tiles/2 + j, -0.1f })*tilescale);
				renderer2d::DrawQuad(quad, m_Color * Vector4({ (float)i / tiles, (float)j / tiles, 1.0f, (float)(i + j) / (2 * tiles) }));
			}

		}
		
		
		renderer2d::EndScene();

		m_Framebuffer->Unbind();
		
	}

	void EditorLayer::OnEvent(Event& event)
	{
		BRCL_TRACE("{0}", event);
		m_CameraController.OnEvent(event);
	}
	
	void EditorImGuiLayer::OnImGuiRender()
	{
		static auto renderdebug = renderer2d::GetStats();
		renderdebug = renderer2d::GetStats();
		
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

		
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f,0.0f });
		ImGui::Begin("Viewport");

		m_isViewportFocused = ImGui::IsWindowFocused() && ImGui::IsWindowHovered();
		m_AppLayer->m_Focused = ImGui::IsWindowFocused();
		
		ImVec2 viewportSize = ImGui::GetContentRegionAvail();
		uint32_t viewportWidth = viewportSize.x;
		uint32_t viewportHeight = viewportSize.y;
		if(m_AppLayer->m_Framebuffer->GetWidth() != viewportWidth ||
			m_AppLayer->m_Framebuffer->GetHeight() != viewportHeight)
		{
			renderer::ResizeViewport(viewportWidth, viewportHeight);
			m_AppLayer->m_Framebuffer->Resize(viewportWidth, viewportHeight);
			m_AppLayer->m_CameraController.Resize(viewportWidth, viewportHeight);
		}
		
		ImGui::Image((void*)m_AppLayer->m_Framebuffer->GetColorAttachmentID(), viewportSize, ImVec2(0,1), ImVec2(1,0));
		
		ImGui::End();
		ImGui::PopStyleVar();

		
		ImGui::Begin("Settings");
		ImGui::Text("Hello");
		ImGui::Text("Draw Calls: %d", renderdebug.DrawCalls);
		ImGui::Text("Quads: %d", renderdebug.QuadCount);
		ImGui::Text("Vertices: %d", renderdebug.GetTotalVertexCount());
		ImGui::Text("Indices: %d", renderdebug.GetTotalIndexCount());
		ImGui::ColorEdit4("Square Color", m_AppLayer->m_Color.data());
		ImGui::DragFloat4("Checker Texture", m_AppLayer->m_TexParams.data(), 0.01f, 0.0f, 20.0f);
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
	void EditorImGuiLayer::OnEvent(Event& event)
	{
		//since the viewport is an imgui window, we need to check which viewport is focused before blocking the event
		if (!m_isViewportFocused) ImGuiLayer::OnEvent(event);
	}
}