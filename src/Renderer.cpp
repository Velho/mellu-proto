#include "Renderer.h"

#include "RenderObject.h"
#include "World.h"

#include "DecorationFile.h"

namespace Proto {

Renderer::Renderer(Level &level, World *world)
{
    init_world(world);
}

Renderer::~Renderer()
{
}

void Renderer::init_world(World *world)
{

}

void Renderer::load_deco()
{

}

void Renderer::load_layout()
{

}

}
