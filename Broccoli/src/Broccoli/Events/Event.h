#pragma once
#include "brclpch.h"



namespace brcl
{

	//For now, events will be blocking

	enum class EventType
	{

		//events will come from windows, apps, keys, and mouse

		None,

		WindowClosed, WindowResized, WindowFocused, WindowLostFocus, WindowMoved,

		AppTick, AppUpdate, AppRender,

		KeyPressed, KeyReleased, TextInput,

		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled

	};

	enum EventCategory
	{
		None,
		EventCategoryApplication = 1 << 0,
		EventCategoryInput = 1 << 1,
		EventCategoryKeyboard = 1 << 2,
		EventCategoryMouse = 1 << 3,
		EventCategoryMouseButton = 1 << 4

	};

	class Event
	{
		//need functions to get: type, name, category flags
		friend class EventDispatcher;

	public:

		virtual ~Event() = default;
		
		virtual EventType GetEventType() const = 0;
		virtual const char* GetEventName() const = 0;
		virtual int GetCategoryFlags() const = 0;

		virtual std::string ToString() const { return GetEventName(); };

		bool GetHandled() const { return m_Handled; }

		bool IsInCategory(EventCategory category) const { return category & GetCategoryFlags(); }

	protected:
		bool m_Handled = false;
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }               \
								virtual EventType GetEventType() const override { return GetStaticType(); } \
								virtual const char* GetEventName() const override { return #type; }         \

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	
	public:

		EventDispatcher(Event& event)
			: m_Event(event) {}

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

		template<typename T>
		void Block()
		{
			if (m_Event.GetEventType() == T::GetStaticType()) m_Event.m_Handled = true;
		}
	
	private:

		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}