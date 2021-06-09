#pragma once
#include "brclpch.h"

#include "Broccoli/Core.h"
#include "Broccoli/Events/Event.h"
#include "Broccoli/Events/ApplicationEvent.h"

namespace brcl
{
	//want a struct that represents the properties of a window (dimensions, title)
	struct WindowProps
	{
		std::string Title;
		int Width;
		int Height;

		WindowProps(const std::string& title = "Broccoli Engine",
			int width = 1280,
			int height = 720)
			: Title(title), Width(width), Height(height) {}


	};

	//interface for a desktop window, to be used by api 
	class BRCL_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual void GetSize(int& width, int& height) const = 0;

		virtual void SetEventCallback(const EventCallbackFn& func) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}