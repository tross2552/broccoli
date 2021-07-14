#pragma once

#include "Broccoli/Window.h"
#include "Broccoli/Renderer/RenderContext.h"
#include <GLFW/glfw3.h>

namespace brcl
{
	class WindowsWindow : public Window
	{
	public:

		WindowsWindow(const WindowProps& props);
		~WindowsWindow() override;

		void OnUpdate() override;

		uint32_t GetWidth() const override { return m_Data.Width; }
		uint32_t GetHeight() const override { return m_Data.Height; }
		void GetSize(uint32_t width, uint32_t height) const override { width = m_Data.Width; height = m_Data.Height; }

		void* GetNativeWindow() const override;

		bool IsVSync() const override { return m_VSync; }
		void SetVSync(bool enabled) override;

		void SetEventCallback(const EventCallbackFn& func) override { m_Data.EventCallback = func; };

	private:

		struct WindowData
		{
			uint32_t Width;
			uint32_t Height;
			std::string Title;

			EventCallbackFn EventCallback;
		};

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:

		GLFWwindow* m_Window;
		std::unique_ptr<RenderContext> m_Context;

		WindowData m_Data;
		bool m_VSync;

	};
	
}


