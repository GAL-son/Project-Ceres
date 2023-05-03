#ifndef APPLICATION_EVENT_H
#define APPLICATION_EVENT_H

#include "Event.h"

class WindowResizedEvent : public Event
{
public:
	WindowResizedEvent(unsigned int width, unsigned int height) : width(width), height(height) {}

	inline unsigned int getWidth() const { return width; }
	inline unsigned int getHeight() const { return height; }

	std::string toString() const override
	{
		std::stringstream ss;
		ss << "WindowResizedEvent: " << width << " ," << height;
		return ss.str();
	}

	EVENT_CLASS_CATEGORY(EventCategoryApplication)
	EVENT_CLASS_TYPE(WindowResized)

private:
	unsigned int width, height;
};

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() {}
	EVENT_CLASS_TYPE(WindowClose)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

#endif // !APPLIATION_EVENT_H
