
add_library( amdvideodriver STATIC
  api/amdvideodriver.h
  src/amdvideodriver.cpp
)

target_include_directories( amdvideodriver
  PUBLIC
    api
)

target_link_libraries( amdvideodriver
  PUBLIC
    videodriver
)

add_subdirectory( src/test )
