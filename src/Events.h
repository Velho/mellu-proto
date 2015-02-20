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

namespace Proto {

class Events {
public:
    Events();
    ~Events();

    enum class EventType {
        None, Platform, Enemy
    };

    void add_event_obj();

private:

};

}

#endif
