#pragma once

#include "Event.h"

namespace brcl
{
	class WindowResizedEvent : public Event
	{

	public:

		WindowResizedEvent(int width, int height)
			: m_Width(width), m_Height(height) {}


		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			//give the event type, coords

			std::stringstream ss;
			ss << GetEventName() << " Event: " << m_Width << "," << m_Height;
			return ss.str();
		}
		
		EVENT_CLASS_TYPE(WindowResized)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	protected:

		uint32_t m_Width;
		uint32_t m_Height;
	};

	class WindowMovedEvent : public Event
	{

	public:

		WindowMovedEvent() = default;

		EVENT_CLASS_TYPE(WindowMoved)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class WindowClosedEvent : public Event
	{

	public:

		WindowClosedEvent() = default;

		EVENT_CLASS_TYPE(WindowClosed)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class WindowFocusedEvent : public Event
	{

	public:

		WindowFocusedEvent() = default;

		EVENT_CLASS_TYPE(WindowFocused)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class WindowLostFocusEvent : public Event
	{

	public:

		EVENT_CLASS_TYPE(WindowLostFocus)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppTickEvent : public Event
	{

	public:

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppUpdateEvent : public Event
	{

	public:

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppRenderEvent : public Event
	{

	public:

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}