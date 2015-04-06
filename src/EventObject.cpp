#include "EventObject.h"
#include "MapObject.h"

namespace Proto {

EventObject::EventObject(const MapObject &mobj) :
    shape{ mobj.get_size() }, event{ nullptr }, id{ 0 }
{
    set_position(mobj.get_position());
    set_color(sf::Color::Red);
}

EventObject::~EventObject()
{
}

void EventObject::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape, states);
}

}
