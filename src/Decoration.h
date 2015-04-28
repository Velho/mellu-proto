#ifndef PROTO_DECO_H
#define PROTO_DECO_H

#include <SFML/Graphics.hpp>

namespace Proto {

/*!
 *\brief Deco class
 */
class Deco : public sf::Drawable {
public:
    Deco();
    ~Deco();

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:
    sf::Sprite decoration;
};

}

#endif
