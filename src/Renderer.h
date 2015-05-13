#ifndef PROTO_RENDERER_H
#define PROTO_RENDERER_H

#include <vector>
#include <memory>

#include "RenderObject.h"

namespace Proto {

class World;
class Level;

class EventObject;
class GameObject;
class MapObject;

class Layout;
class Decoration;

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
     */
    void add_layout(const Layout&);
    /*!
     *\brief
     * Adds new Decoration to renderer.
     */
    void add_decoration(const Decoration&);

private:
    friend class DecorationFile;
    friend class LayoutFile;

    std::vector<std::unique_ptr<RenderObject>> renderable_objs;

    // Renderer manages both Decorations and Layouts
    // but they are not long lived because they are
    // converted to RenderObject's.
    std::vector<std::unique_ptr<Decoration>> deco_objs;
    std::vector<std::unique_ptr<Layout>> layout_objs;

    void init_world(World*);
    void init_layout();

    void load_deco();
    void load_layout();

    void apply_layouts(World*);

    void add_object(EventObject*);
    void add_object(GameObject*);
    void add_object(MapObject*);
};

}

#endif
