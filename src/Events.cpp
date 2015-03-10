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

}

}
