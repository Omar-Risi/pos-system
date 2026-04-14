cmake_minimum_required(VERSION 3.10)
project(pos-system)

# Set C++ to version 17 (prevents errors with modern C++ features)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create the executable from main.cpp
add_executable(pos-system src/main.cpp)
