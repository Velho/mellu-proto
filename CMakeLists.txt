# Velho @ 2014
# project mellu-proto

cmake_minimum_required(VERSION 2.8)
project(mellu-proto)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED graphics window system)

include_directories(${SFML_INCLUDE_DIR})

# Sources
# Important; Entry points 
set(MAINSRC src/Main.cpp)
set(GAMESRC src/Game.h src/Game.cpp)

# Map specific
set(MAPSRC src/Map.h src/Map.cpp)
set(MFILESRC src/MapFile.h src/MapFile.cpp)
set(MAPOBJSRC src/MapObject.h src/MapObject.cpp)

set(WORLDSRC src/World.h src/World.cpp)

# Components TODO Do these provide just the interface?
set(INPUTSRC src/InputComponent.h) # src/InputComponent.cpp)
set(PHYSICSRC src/PhysicsComponent.h) # src/PhysicsComponent.cpp)
set(GRAPHICSRC src/GraphicsComponent.h) #src/GraphicsComponent.cpp)
set(COMPONENTS
    ${INPUTSRC}
    ${PHYSICSRC}
    ${GRAPHICSRC})

# Component container
set(GAMEOBJSRC src/GameObject.h src/GameObject.cpp)

# Player Components
set(PLRINPUT src/PlayerInputComponent.h src/PlayerInputComponent.cpp)
set(PLRPHYSICS src/PlayerPhysicsComponent.h src/PlayerPhysicsComponent.cpp)
set(PLRGRAPHICS src/PlayerGraphicsComponent.h src/PlayerGraphicsComponent.cpp)
set(PLAYERSRC ${PLRINPUT} ${PLRPHYSICS} ${PLRGRAPHICS})

set(SRC_LIST
    ${MAINSRC}
    ${GAMESRC}
    ${MAPSRC}
    ${MFILESRC}
    ${MAPOBJSRC}
    ${WORLDSRC}
    ${COMPONENTS}
    ${GAMEOBJSRC}
    ${PLAYERSRC})

add_executable(mellu-proto ${SRC_LIST})
target_link_libraries(mellu-proto ${SFML_LIBRARIES})
