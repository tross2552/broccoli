#pragma once

#include "Event.h"

#include <sstream>

namespace brcl
{
	class BRCL_API KeyEvent : public Event
	{
		//serves as base class for key pressed and key released
		//need to be able to get key code
	public:
		
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

		
	protected:
		
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}

		int m_KeyCode;
	};

	class BRCL_API KeyPressedEvent : public KeyEvent
	{
		//"repeat" presses will be accounted for here
		//need to be able to get repeat count
	public:

		KeyPressedEvent(int keycode, int repeatCount) :
			KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			//give the event type, keycode, repeatcount

			std::stringstream ss;
			ss << GetEventName() << " Event: " << m_KeyCode << "(" << m_RepeatCount << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;

	};


	class BRCL_API KeyReleasedEvent : public KeyEvent
	{
		//same as keypressed, without "repeats"
	public:

		KeyReleasedEvent(int keycode) :
			KeyEvent(keycode) {}

		std::string ToString() const override
		{
			//give the event type, keycode, repeatcount

			std::stringstream ss;
			ss << GetEventName() << " Event: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)

	};
}
