cmake_minimum_required(VERSION 3.28.1)

project(BulletsManager VERSION 0.0.1 LANGUAGES C CXX OBJC OBJCXX) 

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../.bin/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../.bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../.bin)

add_subdirectory(../externals/glfw ../.build/externals/glfw)
add_subdirectory(../application ../.build/application)