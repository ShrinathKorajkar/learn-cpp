add_library( reaper STATIC
  api/reaper.h
  src/reaper.cpp
)

target_include_directories( reaper
  PUBLIC
    api
)

add_subdirectory( src/test )
