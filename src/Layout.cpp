#include "Layout.h"

namespace Proto {

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
