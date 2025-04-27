
add_library( pixelstuff STATIC
  api/pixelstuff.h
  src/pixelstuff.cpp
)
target_include_directories( pixelstuff
  PUBLIC
    api
)

add_subdirectory( mock )