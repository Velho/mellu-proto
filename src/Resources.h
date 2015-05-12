#ifndef PROTO_RESOURCES_H
#define PROTO_RESOURCES_H

#include <map>
#include <string>
#include <memory>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

namespace Proto {

/*!
 *\brief Fonts enum class
 */ 
enum class Fonts {
    None,
    Arial
};
/*!
 *\brief Textures enum class
 * Textures enum class is used to get
 * correct sf::Texture for specified sprite.
 * Also Textures enum class is used when refering
 * in layout table as integer.
 */
enum class Textures {
    None,
    Testi
};

/*!
 * \brief The Resources class
 * Manages the lifetime of all resources used
 * by this prototype. Fonts, textures, etc.
 * Singleton class.
 */
class Resources {
public:

    ///< Aliases for memory managed pointers.
    using FontPtr = std::unique_ptr<sf::Font>;
    using TexturePtr = std::unique_ptr<sf::Texture>;

    ///< Delete Copy.
    Resources(const Resources&) = delete;
    Resources &operator=(const Resources&) = delete;
    ///< Delete Move.
    Resources(Resources&&) = delete;
    Resources &operator=(Resources&&) = delete;

    ///< Return reference to Resources class.
    static Resources &getInstance()
    {
        static Resources res;
        return res;
    }

    ///< Returns pointer to Font.
    sf::Font *getFont(Fonts);
    sf::Texture *getTex(Textures);

private:
    ///< Constructor available only for internal usage.
    Resources()
    {
        load_fonts(); ///< Load fonts into memory.
        load_textures();    ///< Load textures into memory.
    }

    std::map<Fonts, FontPtr> fonts;
    std::map<Textures, TexturePtr> svgs;

    void load_fonts();
    void load_textures();
};

}

#endif
