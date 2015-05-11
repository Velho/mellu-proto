#include "Layout.h"
#include "Resources.h"
#include "RenderObject.h"

namespace Proto {

Layout::Layout() : Layout(0, 0)
{ }

Layout::Layout(int _id, int _obj_id) :
        Layout(_id, _obj_id, RenderType::None)
{ }

Layout::Layout(int _id, int _obj_id, RenderType type) :
        Layout(_id, _obj_id, type, Textures::None)
{ }

Layout::Layout(int _id, int _obj_id, RenderType type, Textures tex) :
        Layout(_id, _obj_id, type, tex, 0)
{ }

Layout::Layout(
        int _id, int _obj_id,
        RenderType type, Textures text, int prio) :
            id{ _id }, obj_id{ _obj_id },
            obj_type{ type }, texture{ text }, priority{ prio }
    { }

RenderType Layout::get_render_type() const
{
    return obj_type;
}

Textures Layout::get_texture() const
{
    return texture;
}
}
