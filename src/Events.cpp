#include "Events.h"
#include "EventObject.h"

namespace Proto {

Events::Events(std::string level) :
    file{ level }
{
    evt_objs = std::move(file.load());
}

Events::~Events()
{ }

void Events::add_event_obj(EventObject &obj)
{
    evt_objs.emplace_back(new EventObject(obj));
}

void Events::save_objs()
{
    file.save(*this);
}

void Events::draw(sf::RenderTarget &target)
{
    for(auto &o : evt_objs)
        target.draw(*o);
}

}
