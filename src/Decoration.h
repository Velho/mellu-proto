#ifndef PROTO_DECO_H
#define PROTO_DECO_H

#include <SFML/Graphics/Sprite.hpp>

namespace Proto {

enum class Textures;
class MapObject;

/*!
 *\brief Decoration class
 * Describes layout for the Game. For example,
 * World doesnt really get drawn except for the
 * decorations.
 * Decorations gets drawn on the screen
 * with different priorities which are declared in RenderObject
 * class.
 *
 * Decoration size is dictated by the Texture.
 */
class Decoration : public sf::Drawable {
public:
    Decoration() : Decoration(0, sf::Vector2f())
    { }

    Decoration(int i, sf::Vector2f pos) : id{ i }
    {
        set_position(pos);
    }

    Decoration(int i, sf::Vector2f pos, sf::Vector2f sz) : id{ i }
    {
        set_position(pos);
        set_size(sz);
    }

    Decoration(const MapObject&);

    Decoration(const Decoration &cp) :
        decoration{ cp.decoration }, id{ cp.id }
    { }

    Decoration &operator=(const Decoration &cp)
    {
        decoration = cp.decoration;
        id = cp.id;

        return *this;
    }

    ~Decoration();

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

    /*!
     *\brief
     * Sets the sprites position.
     */
    void set_position(sf::Vector2f pos)
    {
        decoration.setPosition(pos);
    }

    /*!
     *\brief
     * Sets the texture size.
     * 
     * Note: You cannot set sprites size like you do with
     * the shapes.
     */
    void set_size(sf::Vector2f sz)
    {
        decoration.setTextureRect(sf::IntRect(sf::Vector2i(),
                    static_cast<sf::Vector2i>(sz)));
    }

    /*!
     *\brief
     * Returns decoration sprites position.
     */
    sf::Vector2f get_position() const
    {
        return decoration.getPosition();
    }
    sf::Vector2f get_size() const;

    /*!
     *\brief
     * Returns Decoration's table index.
     */
    int get_id() const { return id; }

    void set_id(int i) { id = i; }

    void set_texture(sf::Texture *t)
    {
        decoration.setTexture(*t);
    }

private:
    sf::Sprite decoration;
    int id;
};

}

#endif
