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

    EventObject(): event{ nullptr }, evt_table_id{ 0 }, evt_id{ 0 } {}

    EventObject(sf::Vector2f pos, sf::Vector2f sz, int ei, int id) :
        shape{ sz }, evt_table_id{ ei }, evt_id{ id }, event{ nullptr }
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
        shape{ evt.shape }, event{ evt.event }, evt_table_id{ evt.evt_table_id }, evt_id{ evt.evt_id }
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

    void move(sf::Vector2f velocity)
    {
        shape.move(velocity);
    }

    sf::FloatRect get_rect() const { return sf::FloatRect(get_position(), get_size()); }

    /*!
     *\brief
     */
    void set_event(Event*);
    /*!
     *\brief
     * Returns pointer to EventObject's Event.
     *\return Pointer to EventTable's Event, nullptr if id is set to 0.
     */
    Event *get_event() const;

    /*!
     *\brief
     * Returns Event's id.
     *\sa EventTable class
     */
    int get_evt_table_id() const { return evt_table_id; }

    /*!
     *\brief
     * Returns EventObject's index(Index as in table).
     */
    int get_evt_id() const { return evt_id; }

private:
    sf::RectangleShape shape;
    Event *event; ///< Event pointer is managed by the EventObject.
    int evt_table_id;
    int evt_id;

    void set_color(sf::Color clr)
    {
        shape.setFillColor(clr);
    }
};
}

#endif
