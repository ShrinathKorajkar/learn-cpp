add_library( topology STATIC
  api/topology.h
  src/topology.cpp
)

target_include_directories( topology
  PUBLIC
    api
)

add_subdirectory( src/test )
