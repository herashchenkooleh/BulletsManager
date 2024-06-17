find_package(Vulkan REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(platform_sources ${CMAKE_CURRENT_SOURCE_DIR}/sources/Window.mm)
else()
    set(main_window_sources ${CMAKE_CURRENT_SOURCE_DIR}/sources/Window.cpp)
endif()

set(sources_files ${platform_sources} ${CMAKE_CURRENT_SOURCE_DIR}/sources/MainLoop.cpp)
source_group("Source Files\\application" FILES ${sources_files})

set(headers_files ${platform_headers} ${CMAKE_CURRENT_SOURCE_DIR}/includes/bm/MainLoop.hpp)
source_group("Header Files\\application" FILES ${headers_files})

set(main_cpp_file ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp)
source_group("Source Files\\" FILES ${main_cpp_file})

add_executable(${PROJECT_NAME} ${main_cpp_file} ${sources_files} ${headers_files})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes ${VULKAN_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${VULKAN_LIB_LIST} glfw)