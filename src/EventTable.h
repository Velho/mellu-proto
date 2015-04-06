#ifndef PROTO_EVENTTABLE_H
#define PROTO_EVENTTABLE_H

#include "Event.h"

namespace Proto {

class GameObject;
class EventObject;

class Events;

/*!
 * \brief The EventTable class
 * Constructs the Events at compile time for
 * EventObjects to use.
 */
class EventTable {
public:
	using EvtPtr = std::unique_ptr<Event>;
    EventTable(Events&);

    void retrieve_events();

    /*!
     * \brief get_event
     * Returns event out of Event table
     * \return
     */
    Event *get_event(std::size_t);
    Event *operator[](std::size_t);

private:
    std::string level;
    Events &events;
    std::vector<EvtPtr> event_table;

    void load_evts();
    void load_evts_proto();
};
}

#endif

