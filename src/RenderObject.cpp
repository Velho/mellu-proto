#include "RenderObject.h"

#include "GameObject.h"
#include "EventObject.h"
#include "MapObject.h"
#include "Decoration.h"

#include "Layout.h"

#include "Resources.h"

#include "AnimatedPlayer.h"

namespace Proto {

RenderObject::RenderObject() :
    draw_object{ nullptr }, layout{ nullptr }, prio{ -1 }
{
}

RenderObject::RenderObject(
        AnimatedPlayer *g_obj,
        int p) :
    draw_object{ g_obj }, layout{ nullptr }, prio{ p }
{
}

RenderObject::RenderObject(
        EventObject *e_obj,
        const Layout *lay) :
    draw_object{ e_obj }, layout{ lay }, prio{ -1 }
{
    e_obj->set_texture(Resources::getInstance().getTex(lay->get_texture()));
}

RenderObject::RenderObject(
        MapObject *m_obj,
        const Layout *lay) :
    draw_object{ m_obj }, layout{ lay }, prio{ -1 }
{
    m_obj->set_texture(Resources::getInstance().getTex(lay->get_texture()));
}

RenderObject::RenderObject(
        Decoration *deco_obj,
        const Layout *lay) :
    draw_object{ deco_obj }, layout{ lay }, prio{ -1 }
{
    deco_obj->set_texture(Resources::getInstance().getTex(lay->get_texture()));
}

int RenderObject::get_priority() const
{
    if(prio != -1)
        return prio;

    return layout->get_priority();
}
RenderType RenderObject::get_type() const { return layout->get_render_type(); }

}

