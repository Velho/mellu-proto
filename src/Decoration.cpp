#include "Decoration.h"
#include "Resources.h"

#include "MapObject.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace Proto {

Decoration::Decoration(const MapObject &mobj) : id{ 0 }
{
    set_position(mobj.get_position());
}

Decoration::~Decoration()
{
}

void Decoration::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(decoration, states);
}

}
