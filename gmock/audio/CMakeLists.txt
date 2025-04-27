add_library( audio STATIC
  api/audio.h
  src/audio.cpp
)

target_include_directories( audio
  PUBLIC
    api
)

add_subdirectory( src/test )
