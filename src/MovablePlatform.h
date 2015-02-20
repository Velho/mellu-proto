#ifndef PROTO_MOVABLEPLATFORM_H
#define PROTO_MOVABLEPLATFORM_H

#include "MapObject.h"
#include "EventObject.h"

namespace Proto {

class MovablePlatform : public MapObject, public EventObject {
public:

    // Default construction.
    MovablePlatform() : MapObject()
    { }

    MovablePlatform(sf::Vector2f sz) :
        MapObject{ sz }
    { init_clr(); }
    MovablePlatform(sf::Vector2f sz, sf::Vector2f pos) :
        MapObject{ sz, pos }
    { init_clr(); }

    /*!
     * \brief MovablePlatform
     * Create MovablePlatform from MapObject.
     * \param obj
     */
    MovablePlatform(const MapObject &obj) : MapObject{ obj }
    {
        init_clr();
    }

    virtual void draw(sf::RenderTarget &, sf::RenderStates) const;

private:

    void init_clr()
    {
        set_color(sf::Color::Red);
    }
};

}

#endif
