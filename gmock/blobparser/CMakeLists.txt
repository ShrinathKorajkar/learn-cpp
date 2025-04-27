
add_library( blob-parser STATIC
  api/blobparser.h
  src/blobparser.cpp
)

target_include_directories( blob-parser
  PUBLIC
    api
)

add_subdirectory( src/test )
