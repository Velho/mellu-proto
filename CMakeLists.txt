# Velho @ 2014
# project mellu-proto

cmake_minimum_required(VERSION 2.8)
project(mellu-proto)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

set(Boost_USE_STATIC_LIBS ON)

# TODO Add different components this project requires.
find_package(Boost REQUIRED system program_options filesystem)
find_package(SFML 2 REQUIRED graphics window system)
find_package(Sqlite3 REQUIRED) # Find Sqlite3, used for custom fileformat.

# Inlcude directories
include_directories(${Sqlite3_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${SFML_INCLUDE_DIR})

message("Boost LIB_DIR : ${Boost_LIBRARY_DIR}")
message("Boost LIBRARIES : ${Boost_LIBRARIES}")

# Sources
# Important; Entry points 
set(MAINSRC src/Main.cpp)
set(GAMESRC src/Game.h src/Game.cpp)
set(RESSRC src/Resources.h src/Resources.cpp)
set(LVLSRC src/Level.h src/Level.cpp)
set(DBSRC src/Database.h src/Database.cpp)

# Lists all important modules.
set(IMPORTANTSRC 
    ${MAINSRC} ${GAMESRC} 
    ${RESSRC} ${LVLSRC}
    ${DEVCONSRC} ${DBSRC})

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

# Gameplay mechanic
set(DROPGRAPHICS src/DropGraphicsComponent.h src/DropGraphicsComponent.cpp)
set(DROPPHYSICS src/DropPhysicsComponent.h src/DropPhysicsComponent.cpp)
set(DROPINPUT src/DropInputComponent.h src/DropInputComponent.cpp)
#set(DROPOBJSRC src/DropObject.h src/DropObject.cpp)
# aka Manager class
set(DROPPINSRC src/Droppin.h src/Droppin.cpp)
set(EVTFILESRC src/EventFile.h src/EventFile.cpp)
set(EVENTSRC src/Events.h src/Events.cpp)
set(EVENTOBJSRC src/EventObject.h src/EventObject.cpp)

set(MOVEMAPOBJ src/MovablePlatform.h src/MovablePlatform.cpp)

set(EVENTS ${EVTFILESRC} ${EVENTSRC} ${EVENTOBJSRC})
set(DROPMECHANICCMP ${DROPPINSRC} #${EVENTSRC} ${DROPOBJSRC})
    ${DROPGRAPHICS} ${DROPPHYSICS} ${DROPINPUT})

set(SRC_LIST
    ${IMPORTANTSRC}
    ${MAPSRC}
    ${MFILESRC}
    ${MAPOBJSRC}
    ${WORLDSRC}
    ${COMPONENTS}
    ${GAMEOBJSRC}
    ${PLAYERSRC}
    ${DROPMECHANICCMP}
    ${MOVEMAPOBJ}
    ${EVENTS})

add_executable(mellu-proto ${SRC_LIST})
target_link_libraries(mellu-proto ${Boost_LIBRARIES} ${SFML_LIBRARIES} ${Sqlite3_LIBRARY})
