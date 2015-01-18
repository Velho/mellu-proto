#include "World.h"

using Proto::World;

void World::update()
{
    map->update();
}

void World::draw(sf::RenderTarget &target)
{
    map->draw(target);
}

sf::FloatRect World::get_rect(std::size_t idx) const
{
    return map->get_objects()[idx].get_frect();
}
