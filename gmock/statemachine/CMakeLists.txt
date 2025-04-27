
add_library( statemachine STATIC
  api/statemachine.h
  src/statemachine.cpp
)

target_include_directories( statemachine
  PUBLIC
    api
)

add_subdirectory( src/test )
