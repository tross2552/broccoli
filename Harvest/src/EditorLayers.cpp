#include "EditorLayers.h"
#include "imgui/imgui.h"

namespace brcl
{

	class CameraController : public ScriptableEntity
	{
	public:
		
		void OnCreate()
		{
			auto& transform = GetComponent<TransformComponent>().MyTransform;
			transform.SetPosition(Vector3{ 1.0f,1.0f,0.0f });
		}

		void OnDestroy()
		{
		}
		void OnUpdate(Timestep deltaTime)
		{
			auto& transform = GetComponent<TransformComponent>().MyTransform;

			bool rotateFlag = Input::IsKeyPressed(Input::KeyCode::LEFT_SHIFT);
			
			if (Input::IsKeyPressed(Input::KeyCode::W))
			{
				BRCL_CORE_INFO("UP UP UP UP !!!!!!!");
				if (!rotateFlag) transform.SetPosition(transform.GetPosition() + Vector3({ 0.0f, 1.0f, 0.0f }) * deltaTime);
				else transform.SetRotation(transform.GetRotation() + Vector3({ -1.0f,0.0f,0.0f }) * deltaTime);
			}

			if (Input::IsKeyPressed(Input::KeyCode::A))
			{
				BRCL_CORE_INFO("LEFT LEFT LEFT LEFT !!!!!!!");
				if (!rotateFlag) transform.SetPosition(transform.GetPosition() + Vector3({ -1.0f, 0.0f, 0.0f }) * deltaTime);
				else transform.SetRotation(transform.GetRotation() + Vector3({ 0.0f,-1.0f,0.0f }) * deltaTime);
			}

			if (Input::IsKeyPressed(Input::KeyCode::S))
			{
				BRCL_CORE_INFO("DOWN DOWN DOWN DOWN !!!!!!!");
				if (!rotateFlag) transform.SetPosition(transform.GetPosition() + Vector3({ 0.0f, -1.0f, 0.0f }) * deltaTime);
				else transform.SetRotation(transform.GetRotation() + Vector3({ 1.0f,0.0f,0.0f }) * deltaTime);
			}

			if (Input::IsKeyPressed(Input::KeyCode::D))
			{
				BRCL_CORE_INFO("RIGHT RIGHT RIGHT RIGHT !!!!!!!");
				if (!rotateFlag) transform.SetPosition(transform.GetPosition() + Vector3({ 1.0f, 0.0f, 0.0f }) * deltaTime);
				else transform.SetRotation(transform.GetRotation() + Vector3({ 0.0f,1.0f,0.0f }) * deltaTime);
			}

			if (Input::IsKeyPressed(Input::KeyCode::R))
			{
				if (!rotateFlag) transform.SetPosition(transform.GetPosition() + Vector3({ 0.0f, 0.0f, -1.0f }) * deltaTime);
				else transform.SetRotation(transform.GetRotation() + Vector3({ 0.0f,0.0f,-1.0f }) * deltaTime);
			}

			if (Input::IsKeyPressed(Input::KeyCode::F))
			{
				if (!rotateFlag) transform.SetPosition(transform.GetPosition() + Vector3({ 0.0f, 0.0f, 1.0f }) * deltaTime);
				else transform.SetRotation(transform.GetRotation() + Vector3({ 0.0f,0.0f,1.0f }) * deltaTime);
			}

			if (Input::IsKeyPressed(Input::KeyCode::X))
			{
				transform.SetPosition({ 0.0f, 0.0f, 0.0f });
				transform.SetRotation({ 0.0f,0.0f,0.0f });
			}
		}
	};
	
	void EditorLayer::OnAttach()
	{
		m_Texture = Texture2D::Create("assets/textures/broccoli_texture_small_formatted.png");

		FrameBufferSpec fBufferSpec;
		fBufferSpec.Width = 3840; //todo: detect best settings
		fBufferSpec.Height = 2160;
		m_Framebuffer = Framebuffer::Create(fBufferSpec);
		renderer::ResizeViewport(fBufferSpec.Width, fBufferSpec.Height);
		

		m_ActiveScene = std::make_shared<Scene>();

		m_CameraEntity = m_ActiveScene->CreateEntity("Editor Camera");
		m_CameraEntity.AddComponent<CameraComponent>(16.0f/9.0f);
		m_CameraEntity.AddComponent<ScriptComponent>().Bind<CameraController>();
		
		auto square = m_ActiveScene->CreateEntity("Square");
		square.AddComponent<SpriteRendererComponent>();

		m_Color = &square.GetComponent<SpriteRendererComponent>().ColorVector;

		m_ActiveScene->OnPlay();

		m_AspectRatio = ((float)fBufferSpec.Width) / fBufferSpec.Height;
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(Timestep deltaTime)
	{
		BRCL_TRACE("Editor: Update ({0}) ", deltaTime.ToString());
		
		m_CameraEntity.GetComponent<ScriptComponent>().m_Enabled = m_Focused;
		m_CameraEntity.GetComponent<CameraComponent>().MyCamera.SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		

		
		m_Framebuffer->Bind();

		renderer2d::ResetStats();
		
		m_ActiveScene->OnUpdate(deltaTime);
		
		/*
		static float rotation = 0.0f;
		rotation += 0.01f;
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

		}*/

		m_Framebuffer->Unbind();
		
	}

	void EditorLayer::OnEvent(Event& event)
	{
		BRCL_TRACE("{0}", event);
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(BRCL_BIND_EVENT_FN(EditorLayer::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizedEvent>(BRCL_BIND_EVENT_FN(EditorLayer::OnWindowResized));
	}

	bool EditorLayer::OnMouseScrolled(MouseScrolledEvent& event)
	{
		m_ZoomLevel -= event.GetYOffset() * 0.05f; //TODO: curve the controller's zoom
		m_ZoomLevel = std::max(0.05f, m_ZoomLevel);
		return false;
	}

	bool EditorLayer::OnWindowResized(WindowResizedEvent& event)
	{
		m_ActiveScene->OnViewportResize(event.GetWidth(), event.GetHeight());
		return false;
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
			m_AppLayer->m_AspectRatio = ((float)viewportWidth) / viewportHeight;
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
		ImGui::ColorEdit4("Square Color", (float*)m_AppLayer->m_Color);
		ImGui::DragFloat4("Checker Texture", m_AppLayer->m_TexParams.data(), 0.01f, 0.0f, 20.0f);
		ImGui::End();

		ImGui::ShowDemoWindow();

		ImGui::Begin("Scene Hierarchy");
		
		if (ImGui::TreeNode("Active Scene"))
		{
			
			m_AppLayer->m_ActiveScene->m_Registry.each([&] (auto& entityID)
			{
				Entity entity{ entityID, m_AppLayer->m_ActiveScene.get() };
				DrawEntityNode(entity);
				
			} );

			ImGui::TreePop();
		}
		
		ImGui::End();
	}

	void EditorImGuiLayer::DrawEntityNode(Entity entity)
	{
		ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
		const bool is_selected = (entity == m_Selection);
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		if (is_selected)
			node_flags |= ImGuiTreeNodeFlags_Selected;

		bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)entity, node_flags, "%s", tag.c_str());
		if (ImGui::IsItemClicked())
			m_Selection = entity;

		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
			ImGui::Text("This is a drag and drop source");
			ImGui::EndDragDropSource();
		}
		if (node_open)
		{
			ImGui::Text("TestChildNode");
			ImGui::TreePop();
		}
	}
	
	void EditorImGuiLayer::OnEvent(Event& event)
	{
		//since the viewport is an imgui window, we need to check which viewport is focused before blocking the event
		if (!m_isViewportFocused) ImGuiLayer::OnEvent(event);
	}
}