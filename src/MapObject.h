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


    MapObject(const MapObject &obj) :
        shape{ obj.shape }
    { }

    // Move ??

    void set_position(sf::Vector2f);
    void set_size(sf::Vector2f);

    sf::Vector2f get_position() const;
    sf::Vector2f get_size() const;

    sf::FloatRect get_frect() const;

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

private:
    sf::RectangleShape shape;
};

}

#endif
