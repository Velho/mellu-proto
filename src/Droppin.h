#ifndef PROTO_DROPPIN_H
#define PROTO_DROPPIN_H

#include <vector>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "GameObject.h"

namespace Proto {

class Events;
class World;

/*!
 *\brief Droppin class
 * Manages Drops with events.
 */
class Droppin {
public:
	Droppin(Events &evts) : events(evts) { };
	~Droppin() { }

    static std::unique_ptr<GameObject> create_drop();

    /*!
     *\brief
     * Handle input re directs keyboard events to
     * Drop Objects.
     */
    void handle_input(sf::Event&);
    void update(World&);
    void draw(sf::RenderTarget&);

private:
    Events &events;
    std::vector<std::unique_ptr<GameObject>> drop_objs;
};

}

#endif
