#ifndef PROTO_EDITINPUT_H
#define PROTO_EDITINPUT_H

#include <string>
#include <functional>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

namespace Proto {

/*!
 *\brief EditInput class
 * InputEdit takes in input and
 * adds it up to string buffer.
 *
 * Created to take input for Layout
 * system.
 */
class EditInput {
public:

    using InputCallback = std::function<void(std::string)>;

    EditInput();
    EditInput(sf::Vector2f);
    EditInput(sf::Vector2f, InputCallback);

    void handle_input(sf::Event&);
    void update();
    void draw(sf::RenderTarget&);

    InputCallback result_callback;

    void set_position(sf::Vector2f pos)
    {
        textback.setPosition(pos.x, pos.y);
        text.setPosition(pos);
    }

    void set_active(bool a)
    {
        active = a;

        if(!is_active()) // Clear buffer if deactivating.
            buffer.clear();
    }
    bool is_active() const { return active; }

private:
    sf::RectangleShape textback;
    sf::Text text;
    std::string buffer;
    bool active;

    void resize_back();
};
}

#endif

