#ifndef PROTO_EVENTS_H
#define PROTO_EVENTS_H

/**
 * Event status
 *
 * enum class EventStatus {
 *  Trigger,
 *  Progress,
 *  Complete
 * };
 */

#include <vector>

namespace Proto {

class EventObject;

class Events {
public:
    Events();
    ~Events();

    enum class EventType {
        None, Platform, Enemy
    };

    void add_event_obj(const EventObject&);

private:
    std::vector<EventObject*> evt_objs;
};

}

#endif
