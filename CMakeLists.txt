cmake_minimum_required(VERSION 4.0)
project(Practica_1)

set(CMAKE_CXX_STANDARD 20)

file( GLOB MY_FILES *.cpp) #Código fuente de tu proyecto
file ( GLOB GLAD_FILES GLAD/src/*.c) #Código fuente de GLAD
file ( GLOB IMGUI_FILES imgui/src/*.cpp ) #Codigo fuente de IMGUI


add_executable(${PROJECT_NAME} ${MY_FILES}
                               ${GLAD_FILES}
                                ${IMGUI_FILES}
        Renderer.cpp
        Renderer.h
        GUI.cpp
        GUI.h)

target_include_directories( ${PROJECT_NAME} PUBLIC GLAD/include
                                                    imgui/include)

find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL)