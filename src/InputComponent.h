#ifndef PROTO_INPUTCOMPONENT_H
#define PROTO_INPUTCOMPONENT_H

#include <SFML/Window/Event.hpp>

namespace Proto {

class GameObject;

class InputComponent {
public:

    virtual ~InputComponent() {}
    virtual void update(GameObject&, sf::Event&) = 0;
};

}

#endif
