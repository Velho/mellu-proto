#include "MovablePlatform.h"

using Proto::MovablePlatform;

MovablePlatform::~MovablePlatform()
{

}

void MovablePlatform::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    EventObject::draw(target, states);
}
