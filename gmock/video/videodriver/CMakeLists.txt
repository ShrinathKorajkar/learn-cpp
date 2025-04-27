add_library( videodriver INTERFACE )

target_include_directories( videodriver
  INTERFACE
    api
)

add_subdirectory( test )
