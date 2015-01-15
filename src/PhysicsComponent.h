#ifndef PROTO_PHYSICSCOMPONENT_H
#define PROTO_PHYSICSCOMPONENT_H

namespace Proto {

class GameObject;
class World;

class PhysicsComponent {
public:

    virtual ~PhysicsComponent() { }
    virtual void update(GameObject&, World&) = 0;
};
}

#endif
