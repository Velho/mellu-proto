#include "Deco.h"
#include "Resources.h"

namespace Proto {

Deco::Deco()
{
    decoration.setTexture(*Resources::getInstance().getTex(Resources::Textures::Testi));
    //decoration.setTextureRect(sf::IntRect(0, 0, 500, 500));
}

Deco::~Deco()
{
}

void Deco::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(decoration, states);
}

}
