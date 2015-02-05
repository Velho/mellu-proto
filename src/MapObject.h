#ifndef PROTO_MAPOBJECT_H
#define PROTO_MAPOBJECT_H

#include <SFML/Graphics.hpp>

namespace Proto {

/**
 * \brief The MapObject class
 *  Specific object or shape on the Map.
 *  Currently only a placeholder.
 *
 *
 */
class MapObject : public sf::Drawable {
public:
    MapObject() { }
    MapObject(sf::Vector2f sz) :
        shape{ sz }
    { }
    MapObject(sf::Vector2f sz, sf::Vector2f pos) :
        MapObject(sz)
    {
        set_position(pos);
    }

    ///
    /// \brief Copy Ctor MapObject
    /// Copy Constructor MapObject
    /// \param obj
    /// Reference to object from the Copy is made.
    ///
    MapObject(const MapObject &obj) :
        shape{ obj.shape }
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

    sf::Vector2f get_position() const;
    sf::Vector2f get_size() const;

    sf::FloatRect get_frect() const;

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

protected:
    void set_color(sf::Color c)
    {
        shape.setFillColor(c);
    }

private:
    sf::RectangleShape shape;
};

}

#endif
