#ifndef PROTO_EDITTEXT_H
#define PROTO_EDITTEXT_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

namespace Proto {

/*!
 * TODO Add shared base for Edit controls..
 * When lol catz haz time
 */
class EditText {
public:
    //EditText();
    EditText(const sf::Vector2f, const std::string&);

    void update();
    void draw(sf::RenderTarget&);

    void set_position(const sf::Vector2f pos)
    {
        text.setPosition(pos);
        textback.setPosition(pos);
    }
    sf::Vector2f get_position() const { return text.getPosition(); }

    void set_show(bool s) { show = s; }
    bool is_showing() const { return show; }

    void set_string(std::string buf) { buffer = buf; }
    std::string get_string() const { return buffer; }

private:
    sf::RectangleShape textback;
    sf::Text text;
    std::string buffer;
    bool show;
};

}

#endif
