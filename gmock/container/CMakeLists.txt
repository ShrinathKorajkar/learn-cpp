add_library( container STATIC
  api/notavector.h
  src/notavector.cpp
)

target_include_directories( container
  PUBLIC
    api
)

add_subdirectory( src/test )
