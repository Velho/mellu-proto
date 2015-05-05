#include "Droppin.h"

#include "DropInputComponent.h"
#include "DropPhysicsComponent.h"
#include "DropGraphicsComponent.h"

#include "World.h"
#include "Events.h"

#include "GameObject.h"

namespace Proto {

Droppin::Droppin(const Events &evts) :
        events{ evts }, drop_active{ false }, max_drop_count{ 0 }, evt_amount{ 0 }
{ }

Droppin::~Droppin()
{
}

std::unique_ptr<GameObject> Droppin::create_drop()
{
    // Drop GameObject's components.
    std::unique_ptr<DropInputComponent> input{ new DropInputComponent };
    std::unique_ptr<DropPhysicsComponent> physics{ new DropPhysicsComponent(input.get()) };
    std::unique_ptr<DropGraphicsComponent> graphics{ new DropGraphicsComponent(physics.get()) };

    // GameObject grabs the ownership.
    return std::unique_ptr<GameObject>{ new GameObject(input.release(), physics.release(), graphics.release()) };
}

void Droppin::handle_input(sf::Event &event)
{
    if(!drop_active)
        return;

    std::for_each(std::begin(drop_objs), std::end(drop_objs), [&event](std::unique_ptr<GameObject> &d_obj) {
        d_obj->handle_input(event);
    });
}

void Droppin::update(World &world)
{
    if(!drop_active)
        return;

    std::for_each(std::begin(drop_objs), std::end(drop_objs), [&world](std::unique_ptr<GameObject> &d_obj) {
        d_obj->update(world);
    });

    check_active_events();
}

void Droppin::draw(sf::RenderTarget &target)
{
    if(!drop_active)
        return;

    std::for_each(std::begin(drop_objs), std::end(drop_objs), [&target](std::unique_ptr<GameObject> &d_obj) {
        target.draw(*d_obj);
    });
}

void Droppin::activate_event(Event *event)
{
    if(event == nullptr)
        return; // Avoid burn and crash.

    event->set_state(Event::EventState::Trigger);
    active_events.push_back(event);

    evt_amount++;
    set_drop_count();
}

void Droppin::set_drop_count()
{
    if(evt_amount == 1)
        max_drop_count = 4;
    else if(evt_amount == 2)
        max_drop_count = 5;
    else
        max_drop_count = 6;
}

void Droppin::check_active_events()
{
    auto size = active_events.size();

    // Remove all completed event's. Erase/Remove idiom.
    active_events.erase(std::remove_if(active_events.begin(), active_events.end(), [](const Event *e) {
        if(e->get_state() == Event::EventState::Completed)
            return true;
        else
            return false;
    }), active_events.end());

    // Subtract from evt_amount if there was Event's completed.
    if(size > active_events.size())
        evt_amount -= (size - active_events.size());

    if(active_events.empty())
        drop_active = false;
}

void Droppin::update_drops()
{

}

void Droppin::spawn_drop()
{
    if(drop_objs.size() >= max_drop_count) {

    }
}

}
