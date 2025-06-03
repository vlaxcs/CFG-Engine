cmake_minimum_required(VERSION 3.30)
project(CFG_Parser)

set(CMAKE_CXX_STANDARD 20)

add_executable(CFG_Parser main.cpp
        src/Engine.cpp
        src/CFG.cpp)

target_include_directories(CFG_Parser PUBLIC include)