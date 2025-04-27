
add_library( pixelworker STATIC
  api/pixelworker.h
  src/pixelworker.cpp
)
target_include_directories( pixelworker
  PUBLIC
    api
)

target_link_libraries( pixelworker
  PUBLIC
    pixelstuff
)

add_subdirectory( src/test )