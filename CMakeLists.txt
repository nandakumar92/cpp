cmake_minimum_required(VERSION 3.20)

project(cpp_learning)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(classes classes.cpp)
add_executable(containers containers.cpp)
add_executable(templates templates.cpp)
add_executable(threads threads.cpp)
add_executable(files files.cpp)

