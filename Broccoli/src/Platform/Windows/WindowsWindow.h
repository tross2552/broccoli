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

		inline int GetWidth() const override { return m_Data.Width; } //temp
		inline int GetHeight() const override { return m_Data.Height; }

		inline bool IsVSync() const override { return m_VSync; }
		void SetVSync(bool enabled) override;

		inline void SetEventCallback(const EventCallbackFn& func) { m_Data.EventCallback = func; };

	private:

		struct WindowData
		{
			int Width;
			int Height;
			std::string Title;

			EventCallbackFn EventCallback;
		};

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:

		GLFWwindow* m_Window;

		WindowData m_Data;
		bool m_VSync;

	};
	
}


