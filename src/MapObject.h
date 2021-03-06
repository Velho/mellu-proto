#ifndef PROTO_MAPOBJECT_H
#define PROTO_MAPOBJECT_H

#include <SFML/Graphics.hpp>

namespace Proto {

/**
 * \brief The MapObject class
 *  Specific object or shape on the Map.
 * TODO Construction with size first is confusing
 *      => Change the argument order.
 * TODO Fix the dependancy of MapObject class, its HORRIBLE.
 */
class MapObject : public sf::Drawable {
public:
    MapObject() :
        MapObject(sf::Vector2f(), sf::Vector2f(), 0.f, 0)
    { }
    MapObject(sf::Vector2f sz) :
        MapObject(sz, sf::Vector2f(), 0.f, 0) 
    { }
    MapObject(sf::Vector2f sz, sf::Vector2f pos) :
        MapObject(sz, pos, .0f, 0) 
    {
    }

    MapObject(sf::Vector2f sz, sf::Vector2f pos, float angle) :
        MapObject(sz, pos, angle, 0)
    {
    }

    MapObject(sf::Vector2f sz, sf::Vector2f pos, float angle, int i) :
        shape{ sz }, id{ i }
    {
        set_rotation(angle);
        set_position(pos);
    }

    ///
    /// \brief Copy Ctor MapObject
    /// Copy Constructor MapObject
    /// \param obj
    /// Reference to object from the Copy is made.
    ///
    MapObject(const MapObject &obj) :
        shape{ obj.shape }, id{ obj.id }
    { }
    ///
    /// \brief operator =
    /// Copy assignment MapObject.
    /// \param obj
    /// Reference to object from the Copy is made.
    /// \return
    /// Reference to MapObject.
    ///
    MapObject &operator=(const MapObject &obj)
    {
        shape = obj.shape;
        id = obj.id;

        return *this;
    }

    /*!
     * \brief set_position
     * Set position of shape member variable(sf::RectangleShape).
     */
    void set_position(sf::Vector2f);
    /*!
     * \brief set_size
     * Set size of shape member variable(sf::RectangleShape).
     */
    void set_size(sf::Vector2f);

    /*!
     *\brief
     * Returns sf::Vector2f containing MapObject's position as constant.
     */
    sf::Vector2f get_position() const;
    /*!
     *\brief
     * Returns sf::Vector2f containing MapObject's size as constant.
     */
    sf::Vector2f get_size() const;
    /*!
     *\brief
     * Returns sf::FloatRect constructed from position and size.
     * Note, Doesn't take transform into account.
     */
    sf::FloatRect get_frect() const;

    /*!
     *\brief
     * Sets the Event id.
     * Id is index from table.
     */
    void set_id(int _id) { id = _id; }
    /*!
     *\brief
     * Returns id as constant
     */
    int get_id() const { return id; }

    void set_rotation(float);
    float get_rotation() const;

    sf::FloatRect get_global_bounds() const { return shape.getGlobalBounds(); }
    sf::RectangleShape &get_shape() { return shape; }

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

    void set_texture(sf::Texture *t)
    {
        shape.setTexture(t);
    }

    void set_color(sf::Color c)
    {
        shape.setFillColor(c);
    }

private:
    sf::RectangleShape shape; ///< Shape for physics calculations.
    int id; ///< Table index.
};

}

#endif
