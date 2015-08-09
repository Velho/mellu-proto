#ifndef PROTO_SPRITESHEET_H
#define PROTO_SPRITESHEET_H

#include <SFML/Graphics/Texture.hpp>

namespace Proto {

/*!
 *\brief the SpriteSheet class
 * SpriteSheet represents image that
 * contains two or many sprites. Used
 * in animations.
 */
class SpriteSheet {
public:

    /*!
     *\brief
     * Constructs SpriteSheet
     *\param sf::Texture* pointer to the texture.
     *\param sf::Vector2f size of one sprite(or frame).
     */
    SpriteSheet(sf::Texture *, sf::Vector2f)
private:
    sf::Texture *texture;
    sf::Vector2f sprite_size;
};

}


#endif
