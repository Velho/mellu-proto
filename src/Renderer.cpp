#include "Renderer.h"

#include "World.h"

#include "DecorationFile.h"
#include "LayoutFile.h"

#include "Decoration.h"
#include "Layout.h"

#include "GameObject.h"
#include "AnimatedPlayer.h"

#include <algorithm>

namespace Proto {

Renderer::Renderer(Level &lvl, World *w) : level(lvl), world{ w }
{
    load_deco();
    load_layout();

    init_world(world);
}

Renderer::~Renderer()
{
}

void Renderer::add_gobject(AnimatedPlayer *gobject)
{
    renderable_objs.emplace_back(std::unique_ptr<RenderObject>(
            new RenderObject(gobject, 1)));
}

void Renderer::add_layout(const Layout &layout)
{
    // TODO Mess up with constness.
    if(layout.get_id() == 0)
        const_cast<Layout&>(layout).set_id(layout_objs.size() + 1);

    layout_objs.emplace_back(std::unique_ptr<Layout>(new Layout(layout)));

    save_layout();
    init_world(world);
}

void Renderer::add_decoration(const Decoration &decoration)
{
    if(decoration.get_id() == 0)
        const_cast<Decoration&>(decoration).set_id(deco_objs.size() + 1);

    deco_objs.emplace_back(std::unique_ptr<Decoration>(new Decoration(decoration)));
    save_deco();

    init_world(world);

    std::cout << "Deco(" << deco_objs[deco_objs.size() - 1]->get_position().x << ", " << deco_objs[deco_objs.size() - 1]->get_position().y << ")" << std::endl;
}

void Renderer::draw(sf::RenderTarget &target)
{
    if(reset)
        return;

    for(auto &obj : renderable_objs)
        target.draw(*obj->get_drawable());
}

void Renderer::init_world(World *world)
{
    renderable_objs.clear();

    for(auto &lay : layout_objs) {
        if(lay->get_render_type() == RenderType::Decoration) {
            auto deco = get_deco_idx(lay->get_obj_id());

            if(deco != nullptr)
                renderable_objs.emplace_back(std::unique_ptr<RenderObject>(new RenderObject(deco, lay.get())));
        } else if(lay->get_render_type() == RenderType::Map) {
            auto map = world->get_mobj_by_idx(lay->get_obj_id());

            if(map != nullptr)
                renderable_objs.emplace_back(std::unique_ptr<RenderObject>(new RenderObject(map, lay.get())));
        } else if(lay->get_render_type() == RenderType::Event) {
            auto event = world->get_eobj_by_idx(lay->get_obj_id());

            if(event != nullptr)
                renderable_objs.emplace_back(std::unique_ptr<RenderObject>(new RenderObject(event, lay.get())));
        }
    }

    sort_renderables();
}

void Renderer::sort_renderables()
{
    std::sort(renderable_objs.begin(), renderable_objs.end(),
            [](const std::unique_ptr<RenderObject> &f_obj, const std::unique_ptr<RenderObject> &s_obj) {
                return f_obj->get_priority() > s_obj->get_priority();
    });

    reset = false;
}

void Renderer::reset_renderer(World *world)
{
    reset = true;

    load_deco();
    load_layout();

    init_world(world);
}

Decoration *Renderer::get_deco_idx(std::size_t idx)
{
    for(auto &d : deco_objs) {
        if(d->get_id() == idx)
            return d.get();
    }

    return nullptr;
}

void Renderer::load_deco()
{
    DecorationFile file(level.get_current_map_str());

    deco_objs = file.load();
}

void Renderer::load_layout()
{
    LayoutFile file(level.get_current_map_str());

    layout_objs = file.load();
}

void Renderer::save_deco()
{
    DecorationFile file(level.get_current_map_str());

    file.save(*this);
}

void Renderer::save_layout()
{
    LayoutFile file(level.get_current_map_str());

    file.save(*this);
}

}
