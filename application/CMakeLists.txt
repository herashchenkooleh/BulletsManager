find_package(Vulkan REQUIRED)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS program_options log log_setup REQUIRED)
if (NOT BOOST_FOUND)
    message(FATAL_ERROR "Boost not found!")
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(sources_files ${CMAKE_CURRENT_SOURCE_DIR}/sources/Window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/Configs.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/MainLoop.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/Engine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/Entity.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/EngineSubSystem.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/RenderSubSystem.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/Renderer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/VulkanRenderer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/VulkanInstance.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/VulkanLogicalDevice.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/VulkanPhysicalDevice.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/VulkanWindowSurface.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/Logger.cpp)
source_group("Source Files\\application" FILES ${sources_files})

set(headers_files ${CMAKE_CURRENT_SOURCE_DIR}/includes/bm/MainLoop.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/includes/bm/Configs.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/includes/bm/Engine.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/includes/bm/Entity.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/includes/bm/EngineSubSystem.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/includes/bm/RenderSubSystem.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/includes/bm/Renderer.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/includes/bm/VulkanRenderer.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/includes/bm/VulkanInstance.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/includes/bm/VulkanLogicalDevice.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/includes/bm/VulkanPhysicalDevice.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/includes/bm/VulkanWindowSurface.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/includes/bm/Logger.hpp)
source_group("Header Files\\application" FILES ${headers_files})

set(main_cpp_file ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp)
source_group("Source Files\\" FILES ${main_cpp_file})

add_executable(${PROJECT_NAME} ${main_cpp_file} ${sources_files} ${headers_files})

set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG -DVULKAN_HPP_NO_STRUCT_CONSTRUCTORS")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG -DVULKAN_HPP_NO_STRUCT_CONSTRUCTORS")

target_compile_definitions(${PROJECT_NAME} PRIVATE "-DLIBCXX_ENABLE_INCOMPLETE_FEATURES")
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes ${Vulkan_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${Vulkan_LIBRARIES} glfw ${Boost_LIBRARIES})