#include "Decoration.h"
#include "Resources.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace Proto {

Decoration::~Decoration()
{
}

void Decoration::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(decoration, states);
}

}
