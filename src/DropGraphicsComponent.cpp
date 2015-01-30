#include "DropGraphicsComponent.h"
#include "DropPhysicsComponent.h"
#include "Resources.h"

using Proto::DropGraphicsComponent;
using Proto::DropPhysicsComponent;
using Proto::GameObject;

///< Resources
using Proto::Resources;
using Proto::FontId;

constexpr float font_x_offset = 6.f;
constexpr unsigned int font_char_size = 22;

// Character 'I' would prolly need special treatment as it gets rendered too left.

void DropGraphicsComponent::update(GameObject &obj, sf::RenderTarget &target)
{
    //if(obj.get_position() != last_pos)

    drop_shape.setPosition(obj.get_position());
    target_shape.setPosition(physics->target_pos);
    letter.setPosition(sf::Vector2f{ obj.get_position().x + font_x_offset, obj.get_position().y });

    target.draw(drop_shape);
    target.draw(letter);
}


void DropGraphicsComponent::init_text()
{
    letter.setFont(*Resources::getInstance().getFont(FontId::Arial));

    std::string ph_char{ &physics->drop_character };

    letter.setString(ph_char);
    letter.setCharacterSize(font_char_size);
    letter.setColor(sf::Color::Blue);
}
