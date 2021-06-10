#include "brclpch.h"
#include "ImGuiLayer.h"
#include "Broccoli/Application.h"
#include "Platform/OpenGL/imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include "Broccoli/Events/MouseEvent.h"
#include "Broccoli/Events/KeyEvent.h"
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

		//TODO: custom key codes
		io->KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io->KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io->KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io->KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io->KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io->KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io->KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io->KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io->KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io->KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io->KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io->KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io->KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io->KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io->KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io->KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		io->KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io->KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io->KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io->KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io->KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io->KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui::StyleColorsDark();

		ImGui_ImplOpenGL3_Init("#version 460");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
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

		if (m_ReleaseMouse)
		{
			io->MouseDown[0] = false;
			m_ReleaseMouse = false;
		}
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		//TEMPORARY, TODO: REIMPLEMENT ALL OF THIS
		if (dynamic_cast<MouseMovedEvent*>(&event))
		{
		auto& mme = *(MouseMovedEvent*)&event;
		io->MousePos = ImVec2(mme.GetX(), mme.GetY());
		}
		else if (dynamic_cast<MouseButtonPressedEvent*>(&event))
		{
			io->MouseDown[0] = true;
		}
		else if (dynamic_cast<MouseButtonReleasedEvent*>(&event))
		{
			m_ReleaseMouse = true; //set mouse down at the end of the frame, for mouse clicks shorter than 1 frame;
		}
		else if (dynamic_cast<MouseScrolledEvent*>(&event))
		{
			auto& mse = *(MouseScrolledEvent*)&event;

			io->MouseWheelH += (float)mse.GetXOffset();
			io->MouseWheel  += (float)mse.GetYOffset();
		}
		else if (dynamic_cast<KeyPressedEvent*>(&event))
		{
			auto& kde = *(KeyPressedEvent*)&event;
			int key = kde.GetKeyCode();
			if (key >= 0 && key < IM_ARRAYSIZE(io->KeysDown))
				io->KeysDown[key] = true;
			else
				BRCL_CORE_ERROR("ImGui: {0} is not a valid keycode.", key);

			io->KeyCtrl  = io->KeysDown[GLFW_KEY_LEFT_CONTROL] || io->KeysDown[GLFW_KEY_RIGHT_CONTROL];
			io->KeyShift = io->KeysDown[GLFW_KEY_LEFT_SHIFT]   || io->KeysDown[GLFW_KEY_RIGHT_SHIFT];
			io->KeyAlt   = io->KeysDown[GLFW_KEY_LEFT_ALT]     || io->KeysDown[GLFW_KEY_RIGHT_ALT];
		}
		else if (dynamic_cast<KeyReleasedEvent*>(&event))
		{
			auto& kre = *(KeyReleasedEvent*)&event;
			int key = kre.GetKeyCode();
			if (key >= 0 && key < IM_ARRAYSIZE(io->KeysDown))
				io->KeysDown[key] = false;
			else
				BRCL_CORE_ERROR("ImGui: {0} is not a valid keycode.", key);

			io->KeyCtrl  = io->KeysDown[GLFW_KEY_LEFT_CONTROL] || io->KeysDown[GLFW_KEY_RIGHT_CONTROL];
			io->KeyShift = io->KeysDown[GLFW_KEY_LEFT_SHIFT]   || io->KeysDown[GLFW_KEY_RIGHT_SHIFT];
			io->KeyAlt   = io->KeysDown[GLFW_KEY_LEFT_ALT]     || io->KeysDown[GLFW_KEY_RIGHT_ALT];
		}
		

	}

}
