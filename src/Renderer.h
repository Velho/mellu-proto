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

/*!
 *\brief Renderer class
 * Holds up the renderable objects and provides
 * pre rendering logic calls and rendering calls.
 * Renderer manages; Sorting renderable objects, render, 
 */
class Renderer {
public:
    Renderer(Level&, World*);
    ~Renderer();

private:
    friend class DecorationFile;
    friend class LayoutFile;

    std::vector<std::unique_ptr<RenderObject>> renderable_objs;

    void init_world(World*);
    void init_layout();

    void load_deco();
    void load_layout();

    void add_object(EventObject*);
    void add_object(GameObject*);
    void add_object(MapObject*);
};

}

#endif
