
add_library( mailbox STATIC
  api/mailbox.h
  src/mailbox.cpp
)

target_include_directories( mailbox
  PUBLIC
    api
)

add_subdirectory( src/test )
