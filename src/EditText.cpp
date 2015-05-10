#include "EditText.h"

#include "Resources.h"

namespace Proto {

EditText::EditText(const sf::Vector2f pos, const std::string &buf) :
        buffer(buf), show{ false }
{
    text.setFont(*Resources::getInstance().getFont(Fonts::Arial));
    text.setCharacterSize(15);
    text.setColor(sf::Color::White);
    textback.setFillColor(sf::Color::Black);

    set_position(pos);
}

void EditText::update()
{
    if(show) {
        text.setString(buffer);
        textback.setSize(
                sf::Vector2f(text.getGlobalBounds().width, 20));
    }
}

void EditText::draw(sf::RenderTarget &target)
{
    if(show) {
        target.draw(textback);
        target.draw(text);
    }
}

}
