# CMakeLists.txt - buildSystem

cmake_minimum_required(VERSION 3.10)

project(MyProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(my_program main.cpp functions.cpp)

# to run 
# mkdir build   # Create a build directory
# cd build      # Navigate to the build directory
# cmake ..      # Generate build files in the build directory
# make          # Build the executable 'my_program'
# ./my_program  # Runs the executable

