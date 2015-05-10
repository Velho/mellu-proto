#include "RenderObject.h"

#include "GameObject.h"
#include "EventObject.h"
#include "MapObject.h"
#include "Decoration.h"

#include "Layout.h"

namespace Proto {

RenderObject::RenderObject() :
    draw_object{ nullptr },
    priority{ 0 },
    type{ RenderType::None }
{
}

RenderObject::RenderObject(
        const GameObject *g_obj,
        const Layout *lay,
        int p) :
    draw_object{ g_obj }, layout{ lay },
    priority{ p }, type{ RenderType::Game }
{
}

RenderObject::RenderObject(
        const EventObject *e_obj,
        const Layout *lay,
        int p) :
    draw_object{ e_obj }, layout{ lay },
    priority{ p }, type{ RenderType::Event }
{
}

RenderObject::RenderObject(
        const MapObject *m_obj,
        const Layout *lay,
        int p) :
    draw_object{ m_obj }, layout{ lay },
    priority{ p }, type{ RenderType::Map }
{
}

RenderObject::RenderObject(
        const Decoration *deco_obj,
        const Layout *lay,
        int p) :
    draw_object{ deco_obj }, layout{ lay },
    priority{ p }, type{ RenderType::Decoration }
{
}

}

