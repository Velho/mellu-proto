#ifndef PROTO_PLAYEREVENTMANAGER_H
#define PROTO_PLAYEREVENTMANAGER_H

namespace Proto {

class PlayerPhysicsComponent;
class World;

class GameObject;
class EventObject;

/*!
 * \brief The PlayerEventManager class
 * Extends the Basic Player Physics engine
 * to all Event based objects in the game
 * world.
 * + Calculates collisions,
 * + Emit's event,
 * + Track the events.
 * + moarr.
 */
class PlayerEventManager {
public:
    PlayerEventManager(PlayerPhysicsComponent&);

    void update(GameObject&, World&);
private:
    friend class PlayerPhysicsComponent;

    PlayerPhysicsComponent &plr_phy;
    EventObject *evt_obj;

    bool evt_coll{ false };

    void apply_event_collision(GameObject&, World&);

    void complete_event_platform();
    void update_platform_behavior(GameObject&, World&);
};

}

#endif
