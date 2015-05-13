#ifndef PROTO_RENDERABLE_H
#define PROTO_RENDERABLE_H

#include <SFML/Graphics/Drawable.hpp>

namespace Proto {

// Classes that are drawn.
class GameObject;
class MapObject;
class EventObject;
class Decoration;

class Layout;

/*!
 *\brief RenderObject enum class
 * Enumerates different ObjectTypes.
 * Used in the layout table.
 */
enum class RenderType {
    None, Map, Event, Decoration, Game
};

/*!
 *\brief RenderObject class
 * Wraps any sf::Drawable object into
 * pointer for controlling the Rendering
 * process. Template pointer for each object?
 * 
 * std::vector<RenderObject> renderables;
 * std::sort(renderable);
 * void draw(sf::RenderTarget &target) {
 * 
 * }
 *
 * RenderObject is represented as layout table
 * in the maps database.
 */
class RenderObject {
public:
    /*!
     *\brief
     */
    RenderObject();
    /*!
     *\brief
     */
    RenderObject(const GameObject*, const Layout*, int);
    /*!
     *\brief
     */
    RenderObject(const MapObject*, const Layout*, int);
    /*!
     *\brief
     */
    RenderObject(const EventObject*, const Layout*, int);
    /*!
     *\brief
     */
    RenderObject(const Decoration*, const Layout*, int);

    const sf::Drawable &operator()(){return *draw_object;}
    const sf::Drawable *get_drawable() const { return draw_object; }

    Layout const *get_layout() const { return layout; }

    int get_priority() const { return priority; }
    RenderType get_type() const { return type; }

private:
    const sf::Drawable *draw_object;
    const Layout *layout;
    int priority;
    RenderType type;
};

}

#endif

