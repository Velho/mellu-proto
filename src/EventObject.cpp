#include "EventObject.h"
#include "MapObject.h"

#include "Event.h"

namespace Proto {

EventObject::EventObject(const MapObject &mobj) :
    shape{ mobj.get_size() }, event{ nullptr }, evt_id{ 0 }, evt_table_id{ 0 }
{
    set_position(mobj.get_position());
    set_color(sf::Color::Red);
}

EventObject::~EventObject()
{
	if(event != nullptr)
		delete event;
}

void EventObject::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape, states);
}

void EventObject::set_event(Event *e)
{
	event = e;
}

Event *EventObject::get_event() const
{
	return event;
}

}
