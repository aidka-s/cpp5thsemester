cmake_minimum_required(VERSION 3.15)
project(Calculator)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
add_executable(calc
        src/main.cpp
        src/ExpressionEvaluator.cpp
        src/PluginManager.cpp)
