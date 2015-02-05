#include "MovablePlatform.h"

using Proto::MovablePlatform;

void MovablePlatform::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    Proto::MapObject::draw(target, states);
}
