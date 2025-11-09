cmake_minimum_required(VERSION 3.15)
project(Calculator)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
add_executable(calc
        src/main.cpp
        src/ExpressionEvaluator.cpp
        src/PluginManager.cpp)
target_link_libraries(calc PRIVATE ${CMAKE_DL_LIBS})
# Build example plugin (FuncSin)
add_library(funcsin SHARED plugins_src/FuncSin.cpp)
target_include_directories(funcsin PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(funcsin PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/plugins)
# --- Build second plugin (FuncDeg) ---
add_library(funcdeg SHARED plugins_src/FuncDeg.cpp)
target_include_directories(funcdeg PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(funcdeg PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/plugins)

