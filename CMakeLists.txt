cmake_minimum_required(VERSION 3.22)
project(Nuru)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_EXE_LINKER_FLAGS "-static -mwindows")
endif()

add_subdirectory(libs/glfw)

file(GLOB NURU_SRC Nuru/*.cpp)
file(GLOB GLFW_SRC libs/glfw)
file(GLOB IMGUI_SRC libs/imgui/*.cpp)
file(GLOB IMGUI_BACKENDS_SRC libs/imgui/backends/imgui_impl_glfw.cpp libs/imgui/backends/imgui_impl_opengl3.cpp)

#add_definitions(-DIMGUI_USE_WCHAR32)

add_executable(Nuru NuruApp.cpp libs/glad/src/gl.c ${NURU_SRC} ${IMGUI_SRC} ${IMGUI_BACKENDS_SRC})

target_include_directories(Nuru PUBLIC libs/glfw/include)
target_include_directories(Nuru PUBLIC libs/glad/include)
target_include_directories(Nuru PUBLIC libs/imgui libs/imgui/backends)
target_include_directories(Nuru PUBLIC Nuru)

if (UNIX)
    message(STATUS "Linux platform")
    target_link_libraries(Nuru PUBLIC glfw)
endif (UNIX)

if (WIN32)
    message(STATUS "Windows platform")
    target_link_libraries(Nuru PUBLIC glfw)
    target_link_libraries(Nuru PUBLIC gdi32 opengl32 imm32)
endif(WIN32)