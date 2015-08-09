#ifndef PROTO_ANIMATION_H
#define PROTO_ANIMATION_H

#include <vector>

#include <SFML/Graphics/Texture.hpp>

namespace Proto {

enum class Textures;

/*!
 *\brief Animation class
 * Brings SpriteSheet to alive.
 */
class Animation {
public:
    Animation(Textures);
    Animation(Textures, std::size_t);
    Animation(Textures, std::size_t, int);

    sf::Texture *get_texture() const { return texture; }
    sf::IntRect get_frame(std::size_t);
    std::size_t get_framecount() const { return max_frame_count; }
    int get_fps() const { return fps_counter; }

    void insert_frame(sf::IntRect);

private:
    sf::Texture *texture;
    int fps_counter;
    const std::size_t max_frame_count;

    std::vector<sf::IntRect> frames;
};

}

#endif
