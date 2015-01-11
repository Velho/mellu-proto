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

    MapObject(const MapObject &obj) :
        shape{ obj.shape }
    { }

    // Move ??

    void setPosition(sf::Vector2f);
    void setSize(sf::Vector2f);

    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

private:
    sf::RectangleShape shape;
};

}

#endif
