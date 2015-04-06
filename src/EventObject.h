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
class GameObject;
class Event;

/*!
 * \brief The EventObject class
 * Base representation of EventObject's.
 *
 */
class EventObject : public sf::Drawable {
public:

    using EvtObjectPtr = std::unique_ptr<EventObject>;

    EventObject(): event{ nullptr }, id{ 0 } {}

    EventObject(sf::Vector2f pos, sf::Vector2f sz, int i) :
        shape{ sz }, id{ i }
    {
        set_position(pos);
        set_color(sf::Color::Red);
    }

    EventObject(sf::Vector2f pos, sf::Vector2f sz, Event *e) :
    	shape{ sz }, event{ e }
    {
        set_position(pos);
        set_color(sf::Color::Red);
    }

    EventObject(sf::Vector2f pos, sf::Vector2f sz) :
        shape{ sz }, event{ nullptr }
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
        shape{ evt.shape }, event{ evt.event }, id{ evt.id }
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
        shape = evt.shape;
        event = evt.event;

        return *this;
    }

    virtual ~EventObject();

    /*!
     * \brief draw
     * Draw's the shape. Overriden from sf::Drawable object.
     */
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    /*!
     * \brief update
     * Updates the EventObject's behavior according its current state.
     */
    void update();

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

    sf::FloatRect get_rect() const { return sf::FloatRect(get_position(), get_size()); }

    void set_event(Event *e) { event = e; }
    Event *get_event() { return event; }

    int get_id() const { return id; }

private:
    sf::RectangleShape shape;
    Event *event;
    int id;

    void set_color(sf::Color clr)
    {
        shape.setFillColor(clr);
    }
};
}

#endif
