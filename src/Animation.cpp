#include "Animation.h"
#include "Resources.h"

namespace Proto {

Animation::Animation(Textures tx) :
    Animation(tx, 0)
{
}

Animation::Animation(Textures tx, std::size_t max) :
    texture{ Resources::getInstance().getTex(tx) },
    max_frame_count{ max }, fps_counter{ 7 }
{ }

Animation::Animation(Textures tx, std::size_t max, int fps) :
    texture{ Resources::getInstance().getTex(tx) },
    max_frame_count{ max }, fps_counter{ fps }
{ }

void Animation::insert_frame(sf::IntRect rect)
{
    frames.push_back(rect);
}

sf::IntRect Animation::get_frame(std::size_t frame)
{
    return frames[frame];
}

}
