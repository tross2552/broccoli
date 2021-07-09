#pragma once

#include "Event.h"
#include "Broccoli/Input.h"

namespace brcl
{
	class MouseMovedEvent : public Event
	{
		//need to be able to get coords

	public:

		MouseMovedEvent(float x, float y)
			: m_X(x), m_Y(y) {}

		float GetX() const { return m_X; }
		float GetY() const { return m_Y; }

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

	class MouseScrolledEvent : public Event
	{
		//need to be able to get coords

	public:

		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		float GetXOffset() const { return m_XOffset; }
		float GetYOffset() const { return m_YOffset; }

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

	class MouseButtonEvent : public Event
	{
		
	public:

		Input::MouseCode GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)

	protected:

		MouseButtonEvent(Input::MouseCode button)
			: m_Button(button) {}

	protected:
		
		Input::MouseCode m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{

	public:

		MouseButtonPressedEvent(Input::MouseCode button) :
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


	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
		
	public:

		MouseButtonReleasedEvent(Input::MouseCode button) :
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
