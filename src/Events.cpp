#include "Events.h"
#include "EventObject.h"

#include "EventTable.h"
#include "Droppin.h"

namespace Proto {

Events::Events(std::string level) :
	filename(level),
    file(level)
{
    evt_objs = std::move(file.load());
    evt_table = std::unique_ptr<EventTable>{ new EventTable(*this) };
    drop_mech = std::unique_ptr<Droppin>{ new Droppin(*this) };

    init_evts();
}

Events::~Events()
{ }

void Events::add_event_obj(EventObject &obj)
{
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
}

void Events::update()
{
    /*
    for(auto &obj : evt_objs) {
        switch(obj->get_state()) {
            case EventObject::EventState::Idle: break; // Do nothing on idle.

            case EventObject::EventState::Trigger:
                obj->on_trigger(*obj);
            break;
            case EventObject::EventState::Progress:
                obj->on_progress(*obj);
            break;
            case EventObject::EventState::Completed:
                obj->on_completion(*obj);
            break;
        }
    }
    */
}

void Events::init_evts()
{
	evt_table->retrieve_events();

	for(auto &eobj : evt_objs) {
		int id = eobj->get_id();
		eobj->set_event((*evt_table)[id]);
		std::cout << "set event : " << id << std::endl;
	}
}

Droppin *Events::get_droppin()
{
	return drop_mech.get();
}

}
