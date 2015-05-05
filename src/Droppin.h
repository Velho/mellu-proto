#ifndef PROTO_DROPPIN_H
#define PROTO_DROPPIN_H

#include <memory>
#include <vector>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

namespace Proto {

class GameObject;
class Event;
class Events;
class World;

/*!
 *\brief Droppin class
 * Manages Drops with events.
 */
class Droppin {
public:
	Droppin(const Events&);
	~Droppin();

	static std::unique_ptr<GameObject> create_drop();

    /*!
     *\brief
     * Handle input re directs keyboard events to
     * Drop Objects.
     */
    void handle_input(sf::Event&);
    void update(World&);
    void draw(sf::RenderTarget&);

    /*!
     *\brief
     * Activates Event which is passed as argument.
     */
    void activate_event(Event*);

private:
    const Events &events;
    std::vector<std::unique_ptr<GameObject>> drop_objs;
    std::vector<Event*> active_events;

    bool drop_active;   ///< Operate only when event is active.
    int max_drop_count;
    int evt_amount;

    void set_drop_count();
    void check_active_events();

    void update_drops();
    void spawn_drop();
};

}

#endif
