cmake_minimum_required(VERSION 3.10)

# Project Name
project(CppTodo VERSION 1.0)

# Specify C++ Standard (We are using C++20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create the executable from the source files
add_executable(todo 
    src/main.cpp 
    src/TaskManager.cpp
    src/Task.cpp
)

# Note: We don't list .hpp files here, only .cpp files.