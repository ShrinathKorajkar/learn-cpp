# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

project(MyProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(MyLibrary lib/mylib/mylib.cpp)

add_executable(MyExecutable src/main.cpp)
target_include_directories(MyLibrary PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/mylib")
target_link_libraries(MyExecutable PRIVATE MyLibrary)

# 
# set()
set(myVar "Hello, CMake!")
set(myList 1 2 3)
set(myList ${myList} 4 5)  # appending
message("mylist : ${myList}")
function(setVar)
    set(myVar "Inside function" PARENT_SCOPE) # if not mentioned it will be local to function
endfunction()

setVar()
message("Outside function: ${myVar}\n")

#
# project(MyProject HOMEPAGE_URL "https://example.com/myproject")
message("Project Name: ${PROJECT_NAME}")
message("Project Version: ${PROJECT_VERSION}")

# 
# option(ENABLE_DEBUG "Enable debugging information" OFF)
# if (ENABLE_DEBUG)
#     set(CMAKE_BUILD_TYPE Debug)option(ENABLE_DEBUG "Enable debugging information" OFF)
#     add_compile_options(-Wall) 
#     add_subdirectory(docs)
#     add_definitions(-DSPECIAL_FEATURE)
# endif()

# 
add_definitions(-DENABLE_FEATURE_X) # USE IFNDEF
#ifndef ENABLE_FEATURE_X


# 
# # Adding a library with include directories
# add_library(mylib STATIC mylib.cpp)
# target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# # Adding an executable with include directories
# add_executable(myexe main.cpp)
# target_include_directories(myexe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/utils)

# # Adding system include directories
# target_include_directories(myexe SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external-headers)

# # Including directories before default system directories
# target_include_directories(myexe PRIVATE BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/special-include)

# 
# 
# target_compile_options(MyExecutable PRIVATE -Wall -Wextra)
# target_compile_options(MyExecutable
#     PRIVATE
#         $<$<CONFIG:Debug>:-g>
#         $<$<CONFIG:Release>:-O3>
# )

# 
# 
SET(counter 0)
WHILE(counter LESS 5)
    message("Counter: ${counter}")
    MATH(EXPR counter "${counter} + 1")
ENDWHILE()
SET(fruits apple orange banana)
FOREACH(fruit ${fruits})
    message("Fruit: ${fruit}")
ENDFOREACH()
set(MY_VARIABLE "default value" CACHE STRING "Description of MY_VARIABLE")


# find_package(CustomLib REQUIRED)

# if(CUSTOM_LIBRARY_FOUND)
#     message("CustomLibrary found.")
#     include_directories(${CUSTOM_LIBRARY_INCLUDE_DIR})
#     target_link_libraries(MyTarget ${CUSTOM_LIBRARY_LIBRARY})
# else()
#     message(FATAL_ERROR "CustomLibrary not found.")
# endif()

# message(FATAL_ERROR "This CMakeLists.txt file is intended for project authors.")

# Unit tests
# add_executable(test_module1 test/unit_tests/test_module1.cpp)
# add_test(NAME test_module1 COMMAND test_module1)

# add_executable(test_module2 test/unit_tests/test_module2.cpp)
# add_test(NAME test_module2 COMMAND test_module2)

# add_executable(test_common test/unit_tests/test_common.cpp)
# add_test(NAME test_common COMMAND test_common)
