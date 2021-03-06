#include "brclpch.h"
#include "ImGuiLayer.h"
#include "Broccoli/Application.h"
#include "ImGuiBackend.h"
#include "GLFW/glfw3.h"

#include "Broccoli/Events/MouseEvent.h"
#include "Broccoli/Events/KeyEvent.h"

namespace brcl
{

	static inline ImGuiIO* io;

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}
	ImGuiLayer::ImGuiLayer(const std::string& name) : Layer(name) {}

	ImGuiLayer::~ImGuiLayer() {}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		io = &ImGui::GetIO();

		io->BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io->BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 460");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate(Timestep deltaTime)
	{

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		OnImGuiRender();
		ImGui::Render();
		
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::OnImGuiRender()
	{
		static bool show_demo = false;
		if (show_demo)
			ImGui::ShowDemoWindow(&show_demo);
		ImGui::Begin("Another Window");
		ImGui::Checkbox("Demo Window", &show_demo);      // Edit bools storing our window open/close state
		ImGui::End();
	}

	void ImGuiLayer::OnEvent(Event& event)
	{

		//imgui backend installs its own callbacks, so we just need to block events that are being handled

		EventDispatcher dispatcher(event);
		
		if(io->WantCaptureKeyboard)
		{
			dispatcher.Block<KeyPressedEvent>();
			dispatcher.Block<KeyReleasedEvent>();
			dispatcher.Block<TextInputEvent>();
		}

		if(io->WantCaptureMouse)
		{
			dispatcher.Block<MouseScrolledEvent>();
			dispatcher.Block<MouseButtonPressedEvent>();
			dispatcher.Block<MouseButtonReleasedEvent>();
		}

	}

}
