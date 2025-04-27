
add_library( authenticator STATIC
  api/authenticator.h
  src/authenticator.cpp
)
target_include_directories( authenticator
  PUBLIC
    api
)

add_subdirectory( src/test )
add_subdirectory( mock )
