
add_library( session STATIC
  api/session.h
  src/session.cpp
)

target_include_directories( session
  PUBLIC
    api
)

target_link_libraries( session
  PRIVATE
    authenticator
    logger
)

add_subdirectory( src/test )
