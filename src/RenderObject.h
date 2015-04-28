#ifndef PROTO_RENDERABLE_H
#define PROTO_RENDERABLE_H

#include <SFML/Graphics/Drawable.hpp>

namespace Proto {

/*!
 *\brief Importance enum class
 * Priorities RenderObject into three
 * different categories. 
 */
enum class Importance {
    Low, Medium, High
};

// Classes that are drawn.
class GameObject;
class MapObject;
class EventObject;

/*!
 *\brief RenderObject class
 * Wraps any sf::Drawable object into
 * pointer for controlling the Rendering
 * process. Template pointer for each object?
 *
 * std::vector<RenderObject> renderables;
 * void draw(sf::RenderTarget &target) {
 * 
 * }
 */
class RenderObject {
public:
    RenderObject();

    RenderObject(const GameObject&);
    RenderObject(const MapObject&);
    RenderObject(const EventObject&);

private:
    sf::Drawable *draw_object;
    int priority;
};

}

#endif

