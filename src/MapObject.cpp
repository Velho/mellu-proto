#include "MapObject.h"

using Proto::MapObject;

void MapObject::setPosition(sf::Vector2f pos)
{
    shape.setPosition(pos);
}

void MapObject::setSize(sf::Vector2f sz)
{
    shape.setSize(sz);
}

sf::Vector2f MapObject::getPosition() const
{
    return shape.getPosition();
}

sf::Vector2f MapObject::getSize() const
{
    return shape.getSize();
}

void MapObject::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape, states);
}
