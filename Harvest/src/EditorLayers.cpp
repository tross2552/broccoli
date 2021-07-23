#include "EditorLayers.h"
#include "imgui/imgui.h"

namespace brcl
{

	class MovingQuadsScript : public ScriptableEntity
	{
		void OnRender() override
		{
			
			static float rotation = 0.0f;
			rotation += 0.01f;
			Transform quad;
			Vector4 color(1.0f);


			const int tiles = 8;
			const float tilescale = 0.5f;
			quad.SetScale(tilescale * 0.9f);
			for (int i = 0; i < tiles; i++)
			{
				for (int j = 0; j < tiles; j++)
				{
					for(int k = 0; k < tiles; k++)
					{
						quad.SetRotation({ sin(rotation) * j / (tiles), sin(rotation) * i / (tiles), sin(rotation) * (i + j) / (2 * tiles) });
						quad.SetPosition(Vector3({ -(float)tiles / 2 + i  ,  -(float)tiles / 2 + j  ,  -0.1f + k*tilescale }) * tilescale);
						renderer2d::DrawQuad(quad, color * Vector4({ (float)i / tiles, (float)j / tiles, 1.0f, (float)(i + j) / (2 * tiles) }));
					}
					
				}

			}
		}
	};

	class CameraController : public ScriptableEntity
	{
	public:
		
		void OnUpdate(Timestep deltaTime) override
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

		//m_ScriptDemo = m_ActiveScene->CreateEntity("Editor Camera"); //todo: add way to avoid serialization
		//m_ScriptDemo.AddComponent<ScriptComponent>().Bind<MovingQuadsScript>();
		

		m_ActiveScene->OnPlay();

		m_AspectRatio = ((float)fBufferSpec.Width) / fBufferSpec.Height;
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(Timestep deltaTime)
	{
		BRCL_TRACE("Editor: Update ({0}) ", deltaTime.ToString());
		
		m_CameraEntity.GetComponent<ScriptComponent>().Enabled = m_Focused;
		m_CameraEntity.GetComponent<CameraComponent>().MyCamera.SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		
		m_Framebuffer->Bind();

		renderer2d::ResetStats();
		m_ActiveScene->OnUpdate(deltaTime);

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

		ImGui::Begin("Render Stats");
		ImGui::Text("Draw Calls: %d", renderdebug.DrawCalls);
		ImGui::Text("Quads: %d", renderdebug.QuadCount);
		ImGui::Text("Vertices: %d", renderdebug.GetTotalVertexCount());
		ImGui::Text("Indices: %d", renderdebug.GetTotalIndexCount());
		ImGui::End();

		ImGui::ShowDemoWindow();

		ImGui::Begin("Scene Hierarchy");

		if (ImGui::Button("Test Serializer"))
		{
			ImGui::OpenPopup("Test Serializer");
		}

		if (ImGui::BeginPopup("Test Serializer"))
		{
			if (ImGui::MenuItem("Test Serialize"))
			{
				SceneSerializer serializer(m_AppLayer->m_ActiveScene);
				serializer.Serialize("assets/scenes/Test.scene");
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::MenuItem("Test Deserialize"))
			{
				SceneSerializer serializer(m_AppLayer->m_ActiveScene);
				serializer.Deserialize("assets/scenes/Test.scene");
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
		
		if (ImGui::TreeNode("Active Scene"))
		{
			
			for(auto it = m_SceneEntities.begin(); it!= m_SceneEntities.end();it+=1)
			{
				
				std::string label = std::string("").append(it->Name).append("#").append(it->Entity);
				ImGui::Selectable(label.c_str());
				if (ImGui::IsItemClicked() || ImGui::IsItemActive()) m_Selection = it->Entity;
				
				if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
				{
					int copyTo = ImGui::GetMouseDragDelta(0).y < 0.0f ? -1 : 1;

					
					if (it+copyTo >= m_SceneEntities.begin() && it + copyTo != m_SceneEntities.end())
					{
						iter_swap(it, it + copyTo);
						ImGui::ResetMouseDragDelta();
					}
				}

				if (ImGui::BeginPopupContextItem())
				{
					if (ImGui::MenuItem("Delete Entity"))
					{
						it->Deleted = true;
						if (m_Selection == it->Entity) m_Selection = Entity();
					}
					ImGui::EndPopup();
				}
			}

			ImGui::TreePop();
		}

		if(ImGui::BeginPopupContextWindow(0,1,false))
		{
			if(ImGui::MenuItem("Create Empty"))
			{
				AddEntity("Empty");
			}
			if (ImGui::MenuItem("Create Quad"))
			{
				Entity quad = AddEntity("Quad");
				quad.AddComponent<SpriteRendererComponent>();
				
			}
			ImGui::EndPopup();
		}
		
		

		ImGui::End();

		ImGui::Begin("Properties");
		if (m_Selection) DrawEntityComponents(m_Selection);
		
		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("AddComponent");

		if (ImGui::BeginPopup("AddComponent"))
		{
			if (ImGui::MenuItem("Camera"))
			{
				m_Selection.AddComponent<CameraComponent>(m_AppLayer->m_AspectRatio);
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::MenuItem("Sprite Renderer"))
			{
				m_Selection.AddComponent<SpriteRendererComponent>();
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
		ImGui::End();
		

		ClearDeletedEntities();
	}

	Entity EditorImGuiLayer::AddEntity(std::string name)
	{
		auto createdEntity = m_AppLayer->m_ActiveScene->CreateEntity("");
		m_SceneEntities.emplace_back(EditorEntity{ createdEntity, name, false });
		m_EntityCount++;
		return createdEntity;
	}

	void EditorImGuiLayer::ClearDeletedEntities()
	{
		for(auto it = m_SceneEntities.begin(); it != m_SceneEntities.end();)
		{
			if (it->Deleted)
			{
				m_AppLayer->m_ActiveScene->DestroyEntity(it->Entity);
				it = m_SceneEntities.erase(it);
				m_EntityCount--;
			}
			else ++it;
		}
	}

	void EditorImGuiLayer::OnAttach()
	{
		ImGuiLayer::OnAttach();
		ImGuiIO io = ImGui::GetIO();
		io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/Alegreya_Sans/AlegreyaSans-Regular.ttf", 18.0f);

		Application::Get().GetWindow().SetIcon("assets/textures/window_icon.png");

		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.08f, 0.165f, 0.09f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.15f, 0.285f, 0.15f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.405f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.2505f, 0.151f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.15f, 0.285f, 0.15f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.505f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.2505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.15f, 0.285f, 0.15f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.505f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.3505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.2505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.33f, 0.4805f, 0.331f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.3805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.2505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.305f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.2505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.2505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.2505f, 0.151f, 1.0f };

		colors[ImGuiCol_MenuBarBg] = ImVec4{ 0.15f, 0.2505f, 0.151f, 1.0f };
		colors[ImGuiCol_Border] = ImVec4{ 0.15f, 0.2505f, 0.151f, 1.0f };
		
	}

	void EditorImGuiLayer::DrawEntityComponents(Entity entity)
	{
		
		//todo: less oop in components

		
		if(entity.HasComponent<TagComponent>())
		{
			
			auto& tag = entity.GetComponent<TagComponent>().Tag;
			
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy(buffer, tag.c_str());
			
			
			if(ImGui::InputText("Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
			
		}

		if(entity.HasComponent<TransformComponent>())
		{
			auto& transform = entity.GetComponent<TransformComponent>();

			ImGui::SetNextItemOpen(true, ImGuiCond_Once);
			if(ImGui::TreeNode((void*)(intptr_t)1, "Transform Component"))
			{
				Vector3 position = transform.MyTransform.GetPosition();
				Vector3 rotation = transform.MyTransform.GetRotation();
				Vector3 scale = transform.MyTransform.GetScale();

				if (ImGui::InputFloat3("Position", position.data(), "%.5f"))
					transform.MyTransform.SetPosition(position);

				if (ImGui::InputFloat3("Rotation", rotation.data(), "%.5f"))
					transform.MyTransform.SetRotation(rotation);

				if (ImGui::InputFloat3("Scale", scale.data(), "%.5f"))
					transform.MyTransform.SetScale(scale);
				
				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<CameraComponent>())
		{
			auto& camera = entity.GetComponent<CameraComponent>();

			ImGui::SetNextItemOpen(true, ImGuiCond_Once);
			if (ImGui::TreeNode((void*)(intptr_t)2, "Camera Component"))
			{


				float aspect = m_AppLayer->m_AspectRatio;
				float zoom = m_AppLayer->m_ZoomLevel;

				if (ImGui::InputFloat("Aspect Ratio", &aspect, 0, 0, "%.5f"))
					m_AppLayer->m_AspectRatio = aspect;
				if (ImGui::InputFloat("Zoom Level", &zoom, 0, 0, "%.5f"))
					m_AppLayer->m_ZoomLevel = zoom;

				ImGui::TreePop();
			}

			if (ImGui::Button("Remove"))
			{
				ImGui::OpenPopup("Remove Component");
			}

			if (ImGui::BeginPopup("Remove Component"))
			{
				if (ImGui::MenuItem("Remove"))
				{
					m_Selection.RemoveComponent<CameraComponent>(); //todo: lazy delete here
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}

		}

		if(entity.HasComponent<SpriteRendererComponent>())
		{
			auto& renderer = entity.GetComponent<SpriteRendererComponent>();

			ImGui::SetNextItemOpen(true, ImGuiCond_Once);
			if (ImGui::TreeNode((void*)(intptr_t)3, "Sprite Renderer Component"))
			{
				Vector4& color = renderer.ColorVector;
				Vector4& texTransform = renderer.TextureTransform;

				ImGui::ColorEdit4("Color", color.data());
				ImGui::DragFloat4("Texture Transform", texTransform.data(), 0.01f, 0.0f, 20.0f);

				if(ImGui::Button("Remove"))
				{
					ImGui::OpenPopup("Remove Component");
				}

				if (ImGui::BeginPopup("Remove Component"))
				{
					if (ImGui::MenuItem("Remove"))
					{
						m_Selection.RemoveComponent<SpriteRendererComponent>(); //todo: lazy delete here
						ImGui::CloseCurrentPopup();
					}

					ImGui::EndPopup();
				}

				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<ScriptComponent>())
		{
			auto& script = entity.GetComponent<ScriptComponent>();

			ImGui::SetNextItemOpen(true, ImGuiCond_Once);
			if (ImGui::TreeNode((void*)(intptr_t)4, "Script Component"))
			{
				ImGui::Text(script.Enabled ? "Script enabled" : "Script disabled");
				ImGui::TreePop();
			}
		}
	}
	
	void EditorImGuiLayer::OnEvent(Event& event)
	{
		//since the viewport is an imgui window, we need to check which viewport is focused before blocking the event
		if (!m_isViewportFocused) ImGuiLayer::OnEvent(event);
	}
}