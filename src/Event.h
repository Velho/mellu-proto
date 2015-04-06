#ifndef PROTO_EVENT_H
#define PROTO_EVENT_H

#include <boost/signals2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace Proto {

class EventObject;

class Event {
public:
	/*!
	 *\brief EventType enum class
	 * Lists different types of Events.
	 * Simplifies some of the RTTI operations.
	 */
    enum class EventType {
        None, Platform, Enemy
    };
    /*!
     *\brief EventState enum class
     * Lists different states of the Event.
     */
    enum class EventState {
        Idle, Trigger, Progress, Completed
    };

    /*!
     *\brief Event ctor
     * Default constructor for empty Event.
     */
    Event() :
    	id{ 0 },
    	state{ EventState::Idle },
    	type{ EventType::None }
    { }

    /*!
     *\brief Event ctor
     * Constructs Event with appropriate Id.
     */
    Event(int i) :
    	id{ i },
    	type{ EventType::None },
    	state{ EventState::Idle }
    { }

    /*!
     *\brief Event ctor
     * Constructs Event with Id, Type.
     * Default state is Idle(Managed outside of this class).
     */
    Event(int i, EventType t) :
    	id{ i }, type{ t },
    	state{ EventState::Idle }
    { }

    virtual ~Event() { }

    boost::signals2::signal<void (EventObject&)> on_trigger;
    boost::signals2::signal<void (EventObject&)> on_progress;
    boost::signals2::signal<void (EventObject&)> on_completion;

    virtual int get_id() const { return id; }
    virtual void set_id(int i) { id = i; }

    virtual EventType get_type() const { return type; }
    virtual void set_type(EventType t) { type = t; }

    virtual EventState get_state() const { return state; }
    virtual void set_state(EventState s) { state = s; }

    virtual void draw(sf::RenderTarget&) { }

private:
    int id;
    EventType type;
    EventState state;
};

}

#endif
