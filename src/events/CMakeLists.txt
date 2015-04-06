# List of different events the game declares.

include_directories(${CMAKE_SOURCE_DIR}/src/)

set(EVT src/events) # Directory.
set(PLATFORM_SRC ${EVT}/Platform.h ${EVT}/Platform.cpp)

set(SRC_EVENTS
    ${PLATFORM_SRC}
    PARENT_SCOPE) 
