#include "brclpch.h"
#include "ImGuiLayer.h"
#include "Broccoli/Application.h"
#include "ImGuiBackend.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace brcl
{

	static inline ImGuiIO* io;

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

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

	void ImGuiLayer::OnUpdate()
	{

		// Setup time step
		double current_time = glfwGetTime();
		io->DeltaTime = m_Time > 0.0 ? (float)(current_time - m_Time) : (float)(1.0f / 60.0f);
		m_Time = current_time;

		//setup display size
		int w, h;
		Application::Get().GetWindow().GetSize(w, h);
		io->DisplaySize = ImVec2((float)w, (float)h);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		static bool show_demo = false;
		if(show_demo)
			ImGui::ShowDemoWindow(&show_demo);
		ImGui::Begin("Another Window");
		ImGui::Checkbox("Demo Window", &show_demo);      // Edit bools storing our window open/close state
		ImGui::End();

		glClear(GL_COLOR_BUFFER_BIT);
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

	void ImGuiLayer::OnEvent(Event& event)
	{
		

	}

}
