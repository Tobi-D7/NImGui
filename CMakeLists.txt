#Specify Version
cmake_minimum_required(VERSION 3.22)

#Set Project Name
project(NImGui)

#Configuration
option(IMGUI_STD "Enable std::string for ImGui::InputText()" ON)
option(NIMGUI_DOCS "Build Documentation for NImGui" OFF)
option(NIMGUI_PLATFORM_DESKTOP "NImGui for Desktop Platforms" ON)

set(NIMGUI_CFLAGS "")

set(NIMGUI_SOURCE
source/NImGui.cpp
source/stb.cpp
#ImGui Sources
external/imgui/imgui.cpp
external/imgui/imgui_draw.cpp
external/imgui/imgui_demo.cpp
external/imgui/imgui_tables.cpp
external/imgui/imgui_widgets.cpp
external/imgui/backends/imgui_impl_opengl3.cpp)

include_directories(external)

set(NIMGUI_EXTRAINCLUDES "")
set(NIMGUI_EXTRADEPS "")

if(IMGUI_STD)
    set(NIMGUI_SOURCE
    ${NIMGUI_SOURCE}
    external/imgui/misc/cpp/imgui_stdlib.cpp)
    set(NIMGUI_EXTRAINCLUDES
    ${NIMGUI_EXTRAINCLUDES}
    external/imgui/misc/cpp)
endif()
if(NIMGUI_PLATFORM_DESKTOP)
    #Setup GLFW
    set(GLFW_LIBRARY_TYPE "STATIC" CACHE BOOL "Don't want a glfw3.dll/so")
    add_subdirectory(external/glfw glfw)
    set(NIMGUI_SOURCE
    ${NIMGUI_SOURCE}
    #OpenGL Support(3.3+)
    external/glad/glad.c
    external/imgui/backends/imgui_impl_glfw.cpp)
    set(NIMGUI_EXTRAINCLUDES
    ${NIMGUI_EXTRAINCLUDES}
    external/glad
    glfw)
    set(NIMGUI_EXTRADEPS
    ${NIMGUI_EXTRADEPS}
    glfw)
    list(APPEND NIMGUI_CFLAGS -D__DESKTOP__)
endif()

#Add external glfw library
add_library(${PROJECT_NAME} ${NIMGUI_SOURCE})

target_include_directories(${PROJECT_NAME} PUBLIC include external external/imgui ${NIMGUI_EXTRAINCLUDES})

target_link_libraries(${PROJECT_NAME} PUBLIC ${NIMGUI_EXTRADEPS})

target_compile_options(${PROJECT_NAME} PUBLIC ${NIMGUI_CFLAGS})