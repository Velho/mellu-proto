#include "EventObject.h"
#include "MapObject.h"

namespace Proto {

EventObject::EventObject(const MapObject &mobj) :
    position{ mobj.get_position() }, size{ mobj.get_size() }
{
}

EventObject::~EventObject()
{
}

void EventObject::draw(sf::RenderTarget &, sf::RenderStates) const
{

}

}
