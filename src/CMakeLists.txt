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
    ${EVENTS}
    PARENT_SCOPE)

