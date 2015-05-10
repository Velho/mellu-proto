#include "EditInput.h"

#include "Resources.h"

namespace Proto {

EditInput::EditInput() : EditInput(sf::Vector2f())
{
}

EditInput::EditInput(sf::Vector2f pos) : active{ false }
{
    set_position(pos);

    text.setFont(*Resources::getInstance().getFont(Fonts::Arial));
    text.setCharacterSize(15);
    text.setColor(sf::Color::White);

    textback.setFillColor(sf::Color::Black);
}

void EditInput::handle_input(sf::Event &event)
{
    if(event.type == sf::Event::TextEntered) {
        if(event.text.unicode == 8 && buffer.size() != 0) {
            buffer.pop_back();
        } else if(event.text.unicode == 13) {
            if(result_callback != nullptr)
                result_callback(buffer);
            active = false;
        } else if(event.text.unicode > 31 && event.text.unicode < 128)
            buffer += static_cast<char>(event.text.unicode);
    }
}

void EditInput::update()
{
    if(active) {
        text.setString(buffer);
        resize_back();
    }
}

void EditInput::draw(sf::RenderTarget &target)
{
    if(active) {
        target.draw(textback);
        target.draw(text);
    }
}

void EditInput::resize_back()
{
    // Resize according text length
    textback.setSize(
            sf::Vector2f(text.getGlobalBounds().width, 20));
}

}
