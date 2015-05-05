#include "Decoration.h"
#include "Resources.h"

namespace Proto {

Decoration::~Decoration()
{
}

void Decoration::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(decoration, states);
}

}
