#pragma once

#include "Event.h"

#include "Broccoli/Input.h"

namespace brcl
{
	class KeyEvent : public Event
	{

	public:
		
		Input::KeyCode GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

		
	protected:
		
		KeyEvent(Input::KeyCode keycode)
			: m_KeyCode(keycode) {}

		Input::KeyCode m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{

	public:

		KeyPressedEvent(Input::KeyCode keycode, int repeatCount) :
			KeyEvent(keycode), m_RepeatCount(repeatCount) {}


		int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{

			std::stringstream ss;
			ss << GetEventName() << " Event: " << m_KeyCode << "(" << m_RepeatCount << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;

	};


	class KeyReleasedEvent : public KeyEvent
	{

	public:

		KeyReleasedEvent(Input::KeyCode keycode) :
			KeyEvent(keycode) {}

		std::string ToString() const override
		{

			std::stringstream ss;
			ss << GetEventName() << " Event: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)

	};

	class TextInputEvent : public Event
	{
	public:

		TextInputEvent(unsigned int unicode)
			: m_Unicode(unicode) {}

		unsigned int GetChar() const { return m_Unicode; }

		std::string ToString() const override
		{
			//give the event type, offsets

			std::stringstream ss;
			ss << GetEventName() << " Event: " << (char)m_Unicode;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
		EVENT_CLASS_TYPE(TextInput)

	private:

		unsigned int m_Unicode;

	};
}
