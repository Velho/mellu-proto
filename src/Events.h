#ifndef PROTO_EVENTS_H
#define PROTO_EVENTS_H

#include <vector>

#include "EventObject.h"
#include "EventFile.h"

namespace Proto {

class Events {
public:
    Events(std::string);
    ~Events();

    void add_event_obj(EventObject&);

    void save_objs();
    friend void EventFile::save(Events&);

    void draw(sf::RenderTarget&);

    std::vector<EventObject::EvtObjectPtr> &get_evt_objects() { return evt_objs; }

private:
    std::vector<EventObject::EvtObjectPtr> evt_objs;
    EventFile file;
};

}

#endif
