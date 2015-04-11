#include "Platform.h"
#include "../EventObject.h"

namespace Proto {

PROTO_Platform_1::PROTO_Platform_1() :
		Event(1, Event::EventType::Platform)
{
	on_trigger.connect([](EventObject &obj)
	{
		std::cout << "Event Triggered : " << obj.get_id() << std::endl;
		obj.get_event()->set_state(EventState::Progress);
	});

    on_progress.connect([](EventObject &obj)
    {

    });

    on_completion.connect([](EventObject &obj)
    {

    });

	std::cout << "PROTO_Platform_1::PROTO_Platform_1()" << std::endl;
}

}
