#include "Resources.h"

#include <iostream>

using Proto::Resources;

std::string font_dir{ "data/font/" };
std::map<std::string, Resources::Fonts> available_fonts {
    { font_dir + "arial.ttf", Resources::Fonts::Arial }
};

void Resources::load_fonts()
{
    for(auto avf : available_fonts) {
        FontPtr font{ new sf::Font };

        if(!font->loadFromFile(avf.first)) {
            std::cout << "Error loading : " << avf.first << std::endl;
            std::terminate();
        }
        // FonPtr is owned by this container.
        fonts.insert(make_pair(avf.second, std::move(font)));
    }
}

void Resources::load_textures()
{
    // TODO No textures currently to be loaded.
}


sf::Font *Resources::getFont(Resources::Fonts id)
{
    return fonts[id].get();
}
