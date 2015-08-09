#include "Resources.h"

#include <iostream>

namespace Proto {

std::string font_dir{ "data/font/" };
std::map<std::string, Fonts> available_fonts {
    { font_dir + "arial.ttf", Fonts::Arial }
};

std::string svg_dir{ "data/tex/" };
std::map<std::string, Textures> available_svgs {
    { svg_dir + "testi-png.png", Textures::Testi },
    { svg_dir + "idle_vasen.png", Textures::IdleLeft },
    { svg_dir + "idle_oikea.png", Textures::IdleRight },
    { svg_dir + "juoksu_vasen.png", Textures::RunLeft },
    { svg_dir + "juoksu_oikea.png", Textures::RunRight },
    { svg_dir + "aita.png", Textures::Aita },
    { svg_dir + "kavelytaso1.png", Textures::KavelyTaso1 },
    { svg_dir + "kavelytaso2.png", Textures::KavelyTaso2 },
    { svg_dir + "nurtsi1.png", Textures::Nurtsi1 },
    { svg_dir + "nurtsi2.png", Textures::Nurtsi2 },
    { svg_dir + "parveketaso.png", Textures::ParvekeTaso },
    { svg_dir + "parvekeaita.png", Textures::ParvekeAita },
    { svg_dir + "portaat.png", Textures::Portaat },
    { svg_dir + "puu.png", Textures::Puu },
    { svg_dir + "reunamustuus.png", Textures::Reunamustuus },
    { svg_dir + "taivas.png", Textures::Taivas },
    { svg_dir + "takatalo1.png", Textures::Takatalo1 },
    { svg_dir + "takatalo2.png", Textures::Takatalo2 },
    { svg_dir + "talo.png", Textures::Talo },
    { svg_dir + "talo1.png", Textures::Talo1 },
    { svg_dir + "talo2.png", Textures::Talo2 },
    { svg_dir + "talo3.png", Textures::Talo3 },
    { svg_dir + "talo2kpl.png", Textures::TaloDouble },
    { svg_dir + "taloaidalla.png", Textures::TaloAidalla },
    { svg_dir + "vesi.png", Textures::Vesi },
    { svg_dir + "hyppy_oikea.png", Textures::HyppyOikea },
    { svg_dir + "hyppy_vasen.png", Textures::HyppyVasen },
    { svg_dir + "kavelytaso256.png", Textures::KavelyTaso3 },
    { svg_dir + "talo256.png", Textures::Talo4 },
    { svg_dir + "takatalo256.png", Textures::Takatalo3 },
    { svg_dir + "takatalo256_2.png", Textures::Takatalo4 },
    { svg_dir + "nurtsi_iso.png", Textures::NurtsiIso }
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
    std::cout << "Loading textures..." << std::endl;
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

sf::Texture *Resources::getTex(Textures id) const
{
    return svgs.at(id).get();
}

}
