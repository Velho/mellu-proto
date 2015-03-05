#ifndef PROTO_EVENTOBJECT_H
#define PROTO_EVENTOBJECT_H

#include <boost/signals2.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Events.h"

namespace Proto {

/*!
 * \brief The EventObject class
 * Base representation of EventObject's.
 *
 */
class EventObject : public sf::Drawable {
public:
    EventObject() {}

    EventObject(Events::EventType tp, int i) : event_type{ tp }, event_id{ i }
    { }

    EventObject(sf::Vector2f pos, sf::Vector2f sz,
                Events::EventType tp, int tag) :
        position{ pos }, size{ sz }, event_type{ tp }, event_id{ tag }
    { }

    /*!
     * \brief EventObject
     * Copy constructor.
     * \param evt
     * Reference to copy object.
     */
    EventObject(const EventObject &evt) :
        event_type{ evt.event_type }, event_id{ evt.event_id },
        position{ evt.position }, size{ evt.size }
    { }

    /*!
     * \brief operator =
     * Copy assignment.
     * \param evt
     * Copy object.
     * \return
     * Reference to this.
     */
    EventObject &operator=(const EventObject &evt)
    {
        event_type = evt.event_type;
        event_id = evt.event_id;
        position = evt.position;
        size = evt.size;

        return *this;
    }

    virtual ~EventObject();

    //virtual void update();
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

    boost::signals2::signal<void (EventObject&)> on_trigger;
    boost::signals2::signal<void (EventObject&)> on_progress;
    boost::signals2::signal<void (EventObject&)> on_completion;

    Events::EventType get_type() const { return event_type; }
    int get_id() const { return event_id; }

    sf::Vector2f get_position() const { return position; }
    sf::Vector2f get_size() const { return size; }

    void set_position(sf::Vector2f pos)
    {
        position = pos;
        update_shape();
    }

    void set_size(sf::Vector2f sz)
    {
        size = sz;
        update_shape();
    }

protected:
    sf::RectangleShape shape;
    sf::Vector2f position;
    sf::Vector2f size;

    void set_color(sf::Color clr)
    {
        shape.setFillColor(clr);
    }

    /*!
     * \brief update_shape
     * Updates the shape specific variables, position and size.
     */
    void update_shape()
    {
        shape.setPosition(position);
        shape.setSize(size);
    }

private:
    Events::EventType event_type;
    int event_id;
};
}

#endif
