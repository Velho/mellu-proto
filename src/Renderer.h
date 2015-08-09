#ifndef PROTO_RENDERER_H
#define PROTO_RENDERER_H

#include <vector>
#include <memory>

#include "RenderObject.h"
#include <SFML/Graphics/RenderTarget.hpp>

namespace Proto {

class World;
class Level;

class EventObject;
class GameObject;
class MapObject;

class Layout;
class Decoration;

class AnimatedPlayer;

/*!
 *\brief Renderer class
 * Holds up the renderable objects and provides
 * pre rendering logic calls and rendering calls.
 * Renderer manages; Sorting renderable objects, render,
 * layout and decoration objects.
 *
 * In Editor mode when adding Layouts and Decorations,
 * they must be constructed to RenderObjects.
 *
 * The point in RenderObjects are that RenderObject itself
 * doesnt manage the lifetime of the objects it works on.
 * Events and Maps are managed by World aka the Physics Engine,
 * Decorations and Layouts are managed by Renderer aka the Rendering engine.
 */
class Renderer {
public:
    Renderer(Level&, World*);
    ~Renderer();

    /*!
     *\brief
     * Adds new Layout to renderer.
     * Note: If passed Layout has 0 id,
     * the layout will be const_casted and
     * set id. The id set is index in table which
     * is required by the SQL based database.
     */
    void add_layout(const Layout&);

    /*!
     *\brief
     * Adds new Decoration to renderer.
     */
    void add_decoration(const Decoration&);

    /*!
     * Used to add player for rendering purposes.
     * TODO This was hack n slash to get stuff working
     * as faaaast as possibru. FIX THIS PLOX for mankind.
     */
    void add_gobject(AnimatedPlayer*);
    /*!
     *\brief
     * Draws all of the renderobjects.
     */
    void draw(sf::RenderTarget&);

    void reset_renderer(World*);

private:
    friend class DecorationFile;
    friend class LayoutFile;

    World *world;
    const Level &level;

    bool reset{ false };

    std::vector<std::unique_ptr<RenderObject>> renderable_objs;

    // Renderer manages both Decorations and Layouts
    // but they are not long lived because they are
    // converted to RenderObject's.
    std::vector<std::unique_ptr<Decoration>> deco_objs;
    std::vector<std::unique_ptr<Layout>> layout_objs;

    void init_world(World*);
    void init_layout();

    void sort_renderables();

    void load_deco();
    void load_layout();

    void save_deco();
    void save_layout();

    Decoration *get_deco_idx(std::size_t);

    void add_object(EventObject*);
    void add_object(GameObject*);
    void add_object(MapObject*);
};

}

#endif
