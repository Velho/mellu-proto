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
    None,       // 0
    Testi,      // 1
    IdleLeft,   // 2
    RunLeft,    // 3
    RunRight,   // 4
    Aita,       // 5
    KavelyTaso1,// 6
    KavelyTaso2,// 7
    Nurtsi1,    // 8
    Nurtsi2,    // 9
    ParvekeTaso,// 10
    ParvekeAita,// 11
    Portaat,    // 12
    Puu,        // 13
    Reunamustuus,//14
    Taivas,     // 15
    Takatalo1,  // 16
    Takatalo2,  // 17
    Talo,       // 18
    Talo1,      // 19
    Talo2,      // 20
    Talo3,      // 21
    TaloDouble, // 22
    TaloAidalla,// 23
    Vesi,       // 24
    IdleRight,  // 25
    HyppyOikea, // 26
    HyppyVasen, // 27
    KavelyTaso3,// 28 <= 256x256
    Talo4,      // 29 <= 256x256
    Takatalo3,  // 30 <= 256x256
    Takatalo4,  // 31 <= 256x256
    NurtsiIso   // 32 <= 512x512
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
    sf::Texture *getTex(Textures) const;

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
