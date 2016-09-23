# CMakeLists.txt

project(BinarySearchTree)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(BinarySearchTree STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/BinarySearchTree.cpp)

add_executable(Examples ${CMAKE_CURRENT_SOURCE_DIR}/examples/main.cpp)
