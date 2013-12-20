include_directories(../Core)

set(NETWORK_ALL_SOURCES
	NWLApi.cpp
)
add_library(Network ${NETWORK_ALL_SOURCES})
