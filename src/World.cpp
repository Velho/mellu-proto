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
