
add_library( logger STATIC
  api/logger.h
  src/logger.cpp
)

target_include_directories( logger
  PUBLIC
    api
)

add_subdirectory( mock )