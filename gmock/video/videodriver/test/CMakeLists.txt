
add_library( videodriverconformance STATIC
  api/videodriver_paramtest.h
  src/videodriver_paramtest.cpp
)
target_include_directories( videodriverconformance
  PUBLIC
    api
)

find_package(GMock)
target_link_libraries( videodriverconformance
  PUBLIC
    gmock
    gtest
    videodriver
)
