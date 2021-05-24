#pragma once

#include "Event.h"

namespace brcl
{
	class BRCL_API MouseMovedEvent : public Event
	{
		//need to be able to get coords

	public:

		MouseMovedEvent(float x, float y)
			: m_X(x), m_Y(y) {}

		inline float GetX() const { return m_X; }
		inline float GetY() const { return m_Y; }

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		std::string ToString() const override
		{
			//give the event type, coords

			std::stringstream ss;
			ss << GetEventName() << " Event: " << m_X << "," << m_Y;
			return ss.str();
		}

	protected:

		float m_X;
		float m_Y;
	};

	class BRCL_API MouseScrolledEvent : public Event
	{
		//need to be able to get coords

	public:

		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset)
		{
		}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		std::string ToString() const override
		{
			//give the event type, offsets

			std::stringstream ss;
			ss << GetEventName() << " Event: " << m_XOffset << "," << m_YOffset;
			return ss.str();
		}

	protected:

		float m_XOffset;
		float m_YOffset;
	};

	class BRCL_API MouseButtonEvent : public Event
	{
		//serves as base class for button pressed and button released
		//need which button
	public:

		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)

	protected:

		MouseButtonEvent(int button)
			: m_Button(button) {}

		int m_Button;
	};

	class BRCL_API MouseButtonPressedEvent : public MouseButtonEvent
	{

	public:

		MouseButtonPressedEvent(int button) :
			MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			//give the event type, keycode, repeatcount

			std::stringstream ss;
			ss << GetEventName() << " Event: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)

	};


	class BRCL_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
		
	public:

		MouseButtonReleasedEvent(int button) :
			MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			//give the event type, keycode, repeatcount

			std::stringstream ss;
			ss << GetEventName() << " Event: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)

	};
}