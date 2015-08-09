#ifndef PROTO_EVENTS_PLATFORM_H
#define PROTO_EVENTS_PLATFORM_H

#include "../Event.h"

namespace Proto {

/*!
 *\brief
 */
class PROTO_Platform_1 : public Event {
public:
	PROTO_Platform_1();

private:
	const int max_movement{ 200 };
};

/*!
 *\brief
 */
class PROTO_Platform_2 : public Event {
public:
};

}

#endif

