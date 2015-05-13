#include "Renderer.h"

#include "World.h"

#include "DecorationFile.h"
#include "LayoutFile.h"

#include "Decoration.h"
#include "Layout.h"

namespace Proto {

Renderer::Renderer(Level &level, World *world)
{
    init_world(world);
}

Renderer::~Renderer()
{
}

void Renderer::add_layout(const Layout &layout)
{
    // TODO Mess up with constness.
    if(layout.get_id() == 0)
        const_cast<Layout&>(layout).set_id(layout_objs.size() + 1);

    layout_objs.emplace_back(std::unique_ptr<Layout>(new Layout(layout)));
}

void Renderer::add_decoration(const Decoration &decoration)
{
    if(decoration.get_id() == 0)
        const_cast<Decoration&>(decoration).set_id(deco_objs.size() + 1);

    deco_objs.emplace_back(std::unique_ptr<Decoration>(new Decoration(decoration)));
}

void Renderer::init_world(World *world)
{

}

void Renderer::apply_layouts(World *world)
{

}

void Renderer::load_deco()
{

}

void Renderer::load_layout()
{

}

}
