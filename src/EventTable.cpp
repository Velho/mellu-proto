#include "EventTable.h"

#include "GameObject.h"
#include "Events.h"

// Events
#include "events/Platform.h"

#include <map>
#include <vector>
#include <functional>

#include <iostream>

namespace Proto {

EventTable::EventTable(Events &e) : events{ e }, level(e.filename)
{
}

void EventTable::retrieve_events()
{
	load_evts();
}

void EventTable::load_evts()
{
	// TODO Refactor this..
	if(level == "data/maps/proto-evt.map")
		load_evts_proto();
}

void EventTable::load_evts_proto()
{
	event_table.emplace_back(std::unique_ptr<Event>(new PROTO_Platform_1));
	event_table.emplace_back(std::unique_ptr<Event>(new PROTO_Platform_2));
}

Event *EventTable::get_event(std::size_t idx)
{
    for(auto &e : event_table) {
        if(e->get_id() == idx)
            return e.get(); //e.release();
    }

    return nullptr;
}

Event *EventTable::operator [](std::size_t idx)
{
	return event_table[idx].get();
}

}
