#include "Resources.h"

#include <iostream>

namespace Proto {

std::string font_dir{ "data/font/" };
std::map<std::string, Fonts> available_fonts {
    { font_dir + "arial.ttf", Fonts::Arial }
};

std::string svg_dir{ "data/tex/" };
std::map<std::string, Textures> available_svgs {
    { svg_dir + "testi-png.png", Textures::Testi }
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
    for(auto s : available_svgs) {
        TexturePtr t_ptr{ new sf::Texture };

        if(!t_ptr->loadFromFile(s.first)) {
            std::cout << "Error loading : " << s.first << std::endl;
            std::terminate();
        }

        svgs.insert(std::make_pair(s.second, std::move(t_ptr)));
    }
    std::cout << "Textures : " << svgs.size() << std::endl;
}


sf::Font *Resources::getFont(Fonts id)
{
    return fonts[id].get();
}

sf::Texture *Resources::getTex(Textures id)
{
    return svgs[id].get();
}

}
