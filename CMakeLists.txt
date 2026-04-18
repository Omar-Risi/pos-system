cmake_minimum_required(VERSION 3.10)
project(pos-system)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add all source files, including those in subdirectories
add_executable(pos-system 
    src/main.cpp 
    src/utils/menu.cpp
    src/utils/io.cpp
    src/utils/data.cpp
    src/models/product.cpp
)

# Tell CMake to look inside the 'src' folder for header files
target_include_directories(pos-system PRIVATE src)
