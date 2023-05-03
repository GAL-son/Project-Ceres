#ifndef EVENT_CLASS_H
#define EVENT_CLASS_H

#include <string>
#include <functional>
#include <sstream>

enum class EventType
{
	None = 0,
	WindowClose, WindowResized, WindowFocus, WindowLostFocus, WindowMoved,
	KeyPressed, KeyReleased,	
	MouseButtonPresed, MouseButtonReleased, MouseMoved, MouseScrolled
};

// Bitfield
#define BIT(x) (1 << x)

enum EventCategory
{
	None = 0,
	EventCategoryApplication	= BIT(0),
	EventCategoryInput			= BIT(1),
	EventCategoryKeyboard		= BIT(2),
	EventCategoryMouse			= BIT(3),
	EventCategoryMouseButton	= BIT(4)
};

// MACRO to streamline implementation of basic methods
#define EVENT_CLASS_TYPE(type)  static EventType getStaticType() { return EventType::##type; }\
								virtual EventType getEventType() const override { return getStaticType(); }\
								virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

// Base class for events
class Event
{
	friend class EventDispatcher;

public:
	virtual EventType getEventType() const = 0;
	virtual const char* getName() const = 0;
	virtual int getCategoryFlags() const = 0;
	virtual std::string toString() const { return getName(); }

	inline bool isInCategory(EventCategory& category)
	{
		return getCategoryFlags() & category;
	}

	inline bool isEventHandeled() const { return isHandled; }

protected:
	bool isHandled = false;
};

class EventDispatcher
{
	template<typename T>
	using EventFn = std::function<bool(T&)>;

public:	
	EventDispatcher(Event& event) : event(event) {}

	template<typename T>
	bool dispatch(EventFn<T> func)
	{
		if (event.getEventType() == T::getStaticType())
		{
			event.isHandled = func(*(T*) &event);
			return true;
		}
		return false;
	}

private:
	Event& event;
};

#endif // !EVENT_CLASS_H
