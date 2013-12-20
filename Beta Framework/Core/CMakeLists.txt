set(CORE_ALL_SOURCES
		ErrorCatch.cpp MessageServer.cpp WFile.cpp IMessageClient.cpp Object.cpp
		WorldObject.cpp ITickable.cpp WConfigFile.cpp
)
add_library(Core ${CORE_ALL_SOURCES})
