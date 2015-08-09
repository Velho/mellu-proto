#include "Events.h"
#include "EventObject.h"
#include "EventTable.h"

#include "World.h"
#include "Event.h"

#include "Droppin.h"

namespace Proto {

Events::Events(std::string level) :
	filename(level),
    file(level)
{
    evt_objs = std::move(file.load());
    evt_table = std::unique_ptr<EventTable>{ new EventTable(*this) };
    droppin = std::unique_ptr<Droppin>{ new Droppin(*this) };

    init_evts();
}

Events::~Events()
{ }

void Events::add_event_obj(EventObject &obj)
{
    // New eventobject will get the index by the amount of objects in the container.
    if(obj.get_evt_id() == 0)
        obj.set_evt_id(evt_objs.size() + 1);

    evt_objs.emplace_back(std::unique_ptr<EventObject>(new EventObject(obj)));
}

void Events::save_objs()
{
    file.save(*this);
}

void Events::draw(sf::RenderTarget &target)
{
    for(auto &o : evt_objs)
        target.draw(*o);

    droppin->draw(target);
}

void Events::update(World &world)
{
	droppin->update(world);

	update_evts();
}

void Events::init_evts()
{
	evt_table->retrieve_events();

	for(auto &eobj : evt_objs) {
		int id = eobj->get_evt_table_id();
		auto event = (*evt_table)[id];
		eobj->set_event(event);
		//std::cout << "set event : " << id << std::endl;
	}
}

void Events::update_evts()
{
    for(auto &obj : evt_objs) {
        if(obj->get_event() != nullptr) {
			switch(obj->get_event()->get_state()) {
				case Event::EventState::Idle:
				    return; // Do nothing on idle.

				case Event::EventState::Trigger:
					obj->get_event()->on_trigger(*obj);
				break;
				case Event::EventState::Progress:
					obj->get_event()->on_progress(*obj);
				break;
				case Event::EventState::Completed:
					obj->get_event()->on_completion(*obj);
				break;
			}
        }
    }
}

Droppin *Events::get_droppin()
{
	return droppin.get();
}

EventObject *Events::get_by_idx(std::size_t idx)
{
    for(auto &e : evt_objs) {
        if(e->get_evt_id() == idx)
            return e.get();
    }

    return nullptr;
}

}
