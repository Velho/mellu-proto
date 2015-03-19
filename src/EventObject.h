#ifndef PROTO_EVENTOBJECT_H
#define PROTO_EVENTOBJECT_H

#include <boost/signals2.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <memory>

#include <iostream>

namespace Proto {

class MapObject;

/*!
 * \brief The EventObject class
 * Base representation of EventObject's.
 *
 */
class EventObject : public sf::Drawable {
public:

    using EvtObjectPtr = std::unique_ptr<EventObject>;

    enum class EventType {
        None, Platform, Enemy
    };

    EventObject() {}

    EventObject(EventType tp, int i) : event_type{ tp }, event_id{ i }
    { }

    EventObject(sf::Vector2f pos, sf::Vector2f sz,
                EventType tp, int tag) :
        event_type{ tp }, event_id{ tag }, shape{ sz }
    {
        set_position(pos);
        set_color(sf::Color::Red);
    }

    /*!
     * \brief EventObject
     * Constructs EventObject out of MapObject.
     * EventObject and MapObject shares some similarities like
     * position and size.
     */
    EventObject(const MapObject&);

    /*!
     * \brief EventObject
     * Copy constructor.
     * \param evt
     * Reference to copy object.
     */
    EventObject(const EventObject &evt) :
        event_type{ evt.event_type }, event_id{ evt.event_id },
        shape{ evt.shape }
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
        shape = evt.shape;

        return *this;
    }

    virtual ~EventObject();

    //virtual void update();
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

    boost::signals2::signal<void (EventObject&)> on_trigger;
    boost::signals2::signal<void (EventObject&)> on_progress;
    boost::signals2::signal<void (EventObject&)> on_completion;

    EventType get_type() const { return event_type; }
    int get_id() const { return event_id; }

    sf::Vector2f get_position() const { return shape.getPosition(); }
    sf::Vector2f get_size() const { return shape.getSize(); }

    void set_position(sf::Vector2f pos)
    {
        shape.setPosition(pos);
    }

    void set_size(sf::Vector2f sz)
    {
        shape.setPosition(sz);
    }

protected:
    sf::RectangleShape shape;

    void set_color(sf::Color clr)
    {
        shape.setFillColor(clr);
    }

private:
    EventType event_type;
    int event_id;
};
}

#endif
