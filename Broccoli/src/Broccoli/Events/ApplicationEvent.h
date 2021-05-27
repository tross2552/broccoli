#pragma once

#include "Event.h"

namespace brcl
{
	class BRCL_API WindowResizedEvent : public Event
	{

	public:

		WindowResizedEvent(float width, float height)
			: m_Width(width), m_Height(height) {}


		inline float GetWidth() const { return m_Width; }
		inline float GetHeight() const { return m_Height; }

		EVENT_CLASS_TYPE(WindowResized)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

		std::string ToString() const override
		{
			//give the event type, coords

			std::stringstream ss;
			ss << GetEventName() << " Event: " << m_Width << "," << m_Height;
			return ss.str();
		}

	protected:

		float m_Width;
		float m_Height;
	};

	class BRCL_API WindowMovedEvent : public Event
	{

	public:

		EVENT_CLASS_TYPE(WindowMoved)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class BRCL_API WindowClosedEvent : public Event
	{

	public:

		EVENT_CLASS_TYPE(WindowClosed)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class BRCL_API WindowFocusedEvent : public Event
	{

	public:

		EVENT_CLASS_TYPE(WindowFocused)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class BRCL_API WindowLostFocusEvent : public Event
	{

	public:

		EVENT_CLASS_TYPE(WindowLostFocus)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class BRCL_API AppTickEvent : public Event
	{

	public:

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class BRCL_API AppUpdateEvent : public Event
	{

	public:

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class BRCL_API AppRenderEvent : public Event
	{

	public:

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}