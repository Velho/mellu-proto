#include "MapObject.h"

using Proto::MapObject;

void MapObject::set_position(sf::Vector2f pos)
{
    shape.setPosition(pos);
}

void MapObject::set_size(sf::Vector2f sz)
{
    shape.setSize(sz);
}

void MapObject::set_rotation(float angle)
{
    shape.setRotation(angle);
}

sf::Vector2f MapObject::get_position() const
{
    return shape.getPosition();
}

sf::Vector2f MapObject::get_size() const
{
    return shape.getSize();
}

sf::FloatRect MapObject::get_frect() const
{
    return sf::FloatRect{ get_position(), get_size() };
}

float MapObject::get_rotation() const
{
    return shape.getRotation();
}

void MapObject::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape, states);
}
