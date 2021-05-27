#pragma once

#include "Broccoli/Window.h"
#include "GLFW/glfw3.h"

namespace brcl
{
	class WindowsWindow : public Window
	{
	public:

		~WindowsWindow();

		void OnUpdate() override;

		WindowsWindow(const WindowProps& props);

		inline int GetWidth() const override { return m_Width; } //temp
		inline int GetHeight() const override { return m_Height; }

		inline bool IsVSync() const override { return m_VSync; }
		void SetVSync(bool enabled) override;

		inline void SetEventCallback(const EventCallbackFn& func) { m_Callback = func; };

	private:

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:

		GLFWwindow* m_Window;

		std::string m_Title;
		int m_Width;
		int m_Height;
		EventCallbackFn m_Callback;
		bool m_VSync;

	};
	
}


