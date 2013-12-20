include_directories(../Core)

set(AUDIO_ALL_SOURCES
	ASApi.cpp AudioSystem.cpp
)
add_library(Audio ${AUDIO_ALL_SOURCES})
