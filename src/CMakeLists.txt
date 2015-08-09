# Sources
# Important; Entry points 
set(MAINSRC src/Main.cpp)
set(GAMESRC src/Game.h src/Game.cpp)
set(RESSRC src/Resources.h src/Resources.cpp)
set(LVLSRC src/Level.h src/Level.cpp)
set(DBSRC src/Database.h src/Database.cpp)

set(EDITINPUT_SRC src/EditInput.h src/EditInput.cpp)
set(EDITTEXT_SRC src/EditText.h src/EditText.cpp)

# Lists all important modules.
set(IMPORTANTSRC 
    ${MAINSRC} ${GAMESRC} 
    ${RESSRC} ${LVLSRC}
    ${DEVCONSRC} ${DBSRC}
    ${EDITINPUT_SRC} ${EDITTEXT_SRC})

# Rnd Gen
set(RNDGEN_SRC src/RandomGen.h src/RandomGen.cpp)

set(RENDER_SRC src/Renderer.h src/Renderer.cpp)
set(RNDROBJ_SRC src/RenderObject.h src/RenderObject.cpp)
set(RNDR_SRC ${RENDER_SRC} ${RNDROBJ_SRC})

set(LAYOUTFILE_SRC src/LayoutFile.h src/LayoutFile.cpp)
set(LAYOBJ_SRC src/Layout.h src/Layout.cpp)
set(LAYOUT_SRC ${LAYOUTFILE_SRC} ${LAYOBJ_SRC})

# Map specific
set(MAPSRC src/Map.h src/Map.cpp)
set(MFILESRC src/MapFile.h src/MapFile.cpp)
set(MAPOBJSRC src/MapObject.h src/MapObject.cpp)

set(DECOIMP_SRC src/Decoration.h src/Decoration.cpp)
set(DECOFILE_SRC src/DecorationFile.h src/DecorationFile.cpp)
set(DECO_SRC ${DECOIMP_SRC} ${DECOFILE_SRC})

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
set(PLREVENTMGR src/PlayerEventManager.h src/PlayerEventManager.cpp)
set(PLAYERSRC ${PLRINPUT} ${PLRPHYSICS} ${PLRGRAPHICS} ${PLREVENTMGR})

# Gameplay mechanic
set(DROPGRAPHICS src/DropGraphicsComponent.h src/DropGraphicsComponent.cpp)
set(DROPPHYSICS src/DropPhysicsComponent.h src/DropPhysicsComponent.cpp)
set(DROPINPUT src/DropInputComponent.h src/DropInputComponent.cpp)
#set(DROPOBJSRC src/DropObject.h src/DropObject.cpp)
# aka Manager class
set(DROPPINSRC src/Droppin.h src/Droppin.cpp)
set(EVTBASE src/Event.h)
set(EVTFILESRC src/EventFile.h src/EventFile.cpp)
set(EVENTSRC src/Events.h src/Events.cpp)
set(EVENTOBJSRC src/EventObject.h src/EventObject.cpp)
set(EVTTABLESRC src/EventTable.h src/EventTable.cpp)

set(EVENTS ${EVTBASE} ${EVTFILESRC} ${EVENTSRC} ${EVENTOBJSRC} ${EVTTABLESRC})
set(DROPMECHANICCMP ${DROPPINSRC} #${EVENTSRC} ${DROPOBJSRC})
    ${DROPGRAPHICS} ${DROPPHYSICS} ${DROPINPUT})

set(AABB_SRC src/BoundingBox.h src/BoundingBox.cpp)

# Animations & Spritesheets.
set(SSHEET_SRC src/SpriteSheet.h src/SpriteSheet.cpp)
set(ANIM src/Animation.h src/Animation.cpp)
set(ANIMPLR_SRC src/AnimatedPlayer.h src/AnimatedPlayer.cpp)

set(ANIM_SRC ${SSHEET_SRC} ${ANIM} ${ANIMPLR_SRC})

set(ALOITUS_SRC src/AloitusRuutu.h src/AloitusRuutu.cpp)

# Add events
add_subdirectory(events)

set(SRC_LIST
    ${IMPORTANTSRC}
    ${RNDGEN_SRC}
    ${RNDR_SRC}
    ${MAPSRC}
    ${MFILESRC}
    ${MAPOBJSRC}
    ${DECO_SRC}
    ${WORLDSRC}
    ${COMPONENTS}
    ${GAMEOBJSRC}
    ${PLAYERSRC}
    ${DROPMECHANICCMP}
    ${MOVEMAPOBJ}
    ${EVENTS}
    ${SRC_EVENTS}
    ${AABB_SRC}
    ${LAYOUT_SRC}
    ${ANIM_SRC}
    ${ALOITUS_SRC}
    PARENT_SCOPE)

