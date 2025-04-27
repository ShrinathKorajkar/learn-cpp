add_library( string-utils STATIC
  api/stringutils.h
  src/stringutils.cpp
)

target_include_directories( string-utils
  PUBLIC
    api
)

add_subdirectory( src/test )
