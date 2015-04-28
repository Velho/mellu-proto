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

    /*!
     *\brief
     * Initializes event_table with smart pointers
     * to Event. Retrieve events before returning pointers
     * to them.
     */
    void retrieve_events();

    /*!
     * \brief get_event
     * Returns event out of Event table.
     * Out as its ownership is released.
     * \return
     * Pointer to Event by index.
     */
    Event *get_event(std::size_t);
    /*!
     *\brief operator[]
     * Uses get_event(..) behind the scenes to return
     * Event pointer correctly.
     */
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

