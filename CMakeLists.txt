cmake_minimum_required(VERSION 3.30)
project(CFG-Engine)

set(CMAKE_CXX_STANDARD 20)

add_executable(CFG-Engine main.cpp
        src/Engine.cpp
        src/CFG.cpp)

target_include_directories(CFG-Engine PUBLIC include)
