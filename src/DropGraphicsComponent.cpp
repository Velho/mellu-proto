#include "DropGraphicsComponent.h"
#include "DropPhysicsComponent.h"
#include "Resources.h"

#include "GameObject.h"

namespace Proto {

const float font_x_offset = 6.f;
const unsigned int font_char_size = 22;

// Character 'I' would prolly need special treatment as it gets rendered too left.

void DropGraphicsComponent::update(GameObject &obj)
{
    //if(obj.get_position() != last_pos)

    drop_shape.setPosition(obj.get_position());
    target_shape.setPosition(physics->target_pos);
    letter.setPosition(sf::Vector2f{ obj.get_position().x + font_x_offset, obj.get_position().y });
}

void DropGraphicsComponent::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(drop_shape);
    target.draw(letter);
}


void DropGraphicsComponent::init_text()
{
    letter.setFont(*Resources::getInstance().getFont(Resources::Fonts::Arial));

    std::string ph_char{ &physics->drop_character };

    letter.setString(ph_char);
    letter.setCharacterSize(font_char_size);
    letter.setColor(sf::Color::Blue);
}
}
