#ifndef PROTO_MOVABLEPLATFORM_H
#define PROTO_MOVABLEPLATFORM_H

#include "EventObject.h"

namespace Proto {

class MovablePlatform : public EventObject {
public:

    // Default construction.
    MovablePlatform() : EventObject()
    {
        init_clr();
    }

    virtual ~MovablePlatform();

    //virtual void update() override;
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;

private:

    void init_clr()
    {
        set_color(sf::Color::Red);
    }
};

}

#endif
