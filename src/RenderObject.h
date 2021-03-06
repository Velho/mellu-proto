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

class AnimatedPlayer;

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
    RenderObject(AnimatedPlayer*, int);
    /*!
     *\brief
     */
    RenderObject(MapObject*, const Layout*);
    /*!
     *\brief
     */
    RenderObject(EventObject*, const Layout*);
    /*!
     *\brief
     */
    RenderObject(Decoration*, const Layout*);

    RenderObject(const RenderObject &cp) :
        draw_object{ cp.draw_object }, layout{ cp.layout }
    { }

    RenderObject &operator=(const RenderObject &cp)
    {
        draw_object = cp.draw_object;
        layout = cp.layout;

        return *this;
    }

    const sf::Drawable &operator()(){return *draw_object;}
    sf::Drawable *get_drawable() const { return draw_object; }

    Layout const *get_layout() const { return layout; }

    int get_priority() const;
    RenderType get_type() const;

private:
    sf::Drawable *draw_object;
    const Layout *layout;
    int prio;
};

}

#endif

