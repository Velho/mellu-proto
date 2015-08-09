#ifndef PROTO_MOVABLEPLATFORM_H
#define PROTO_MOVABLEPLATFORM_H

#include "EventObject.h"

namespace Proto {

/*!
 * \brief The MovablePlatform class
 * Implements Platform specific stuff,
 * velocity, etc.
 * TODO Make sure velocity get init correctly
 *      => Re-declare constructors from EventObject(??).
 */
class MovablePlatform : public EventObject {
public:
    virtual ~MovablePlatform();

    //virtual void update() override;
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;

    void set_velocity(sf::Vector2f v) { velocity = v; }
    sf::Vector2f get_velocity() const { return velocity; }

private:
    sf::Vector2f velocity;

    void init_clr()
    {
        set_color(sf::Color::Red);
    }
};

}

#endif
