cmake_minimum_required(VERSION 2.8)
project(kenney-proto)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED graphics window system)

include_directories(${SFML_INCLUDE_DIR})

# Sources
set(MAINSRC src/Main.cpp)
set(GAMESRC src/Game.h src/Game.cpp)

set(MAPSRC src/Map.h src/Map.cpp)
set(MFILESRC src/MapFile.h src/MapFile.cpp)
set(MAPOBJSRC src/MapObject.h src/MapObject.cpp)


set(SRC_LIST
    ${MAINSRC}
    ${GAMESRC}
    ${MAPSRC}
    ${MFILESRC}
    ${MAPOBJSRC})

add_executable(kenney-proto ${SRC_LIST})
target_link_libraries(kenney-proto ${SFML_LIBRARIES})
