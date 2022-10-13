cmake_minimum_required(VERSION 3.22)

project(DesktopApp)

add_subdirectory(../ NImGui)

add_executable(${PROJECT_NAME} ${PROJECT_NAME}/main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE NImGui)

target_link_libraries(${PROJECT_NAME} NImGui)