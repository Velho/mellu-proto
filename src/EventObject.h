#ifndef PROTO_EVENTOBJECT_H
#define PROTO_EVENTOBJECT_H

#include <boost/signals2.hpp>

namespace Proto {

class EventObject {
public:
    EventObject(int i) : id{ i }
    { }
    virtual ~EventObject() {}

    boost::signals2::signal<void (EventObject&)> on_trigger;
    boost::signals2::signal<void (EventObject&)> on_progress;
    boost::signals2::signal<void (EventObject&)> on_completion;

    int get_id() const { return id; }

private:
    int id;
};
}

#endif
