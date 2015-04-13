#ifndef PROTO_EVENTS_H
#define PROTO_EVENTS_H

#include "EventObject.h"
#include "EventFile.h"

#include "EventTable.h"

#include <vector>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace Proto {

class World;
class Droppin;

class Events {
public:
    Events(std::string);
    ~Events();

    void add_event_obj(EventObject&);

    void save_objs();
    friend void EventFile::save(Events&);

    void draw(sf::RenderTarget&); ///< Draw the EventObjects.
    void update(World&); ///< Update the event objects behavior.

    std::vector<EventObject::EvtObjectPtr> &get_evt_objects() { return evt_objs; }
    Droppin *get_droppin(); ///< Returns ref to Droppin. Input is required.

private:
    friend class EventTable;
    std::unique_ptr<EventTable> evt_table;
    std::unique_ptr<Droppin> droppin;
    std::vector<EventObject::EvtObjectPtr> evt_objs;
    EventFile file;
    std::string filename;

    void init_evts();	///< Initializes event's.
    void update_evts();	///< Updates event's behavior(skip nullptr).
};

}

#endif
