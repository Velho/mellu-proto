#ifndef PROTO_DROPEVENT_H
#define PROTO_DROPEVENT_H

namespace Proto {

class Event {
public:
    Event();
    ~Event();

    enum class EventStatus {
        Trigger,
        Progress,
        Complete
    };

private:
};

}

#endif
