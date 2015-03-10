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

    friend void EventFile::save(Events&);

private:
    std::vector<EventObject::EvtObjectPtr> evt_objs;
    EventFile file;
};

}

#endif
