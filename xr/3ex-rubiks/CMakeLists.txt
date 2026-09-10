cmake_minimum_required(VERSION 4.3)
project(3ex_rubiks)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 3 REQUIRED COMPONENTS Window)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_library(OPENGL_LIBRARY OpenGL REQUIRED)
find_library(GLUT_LIBRARY GLUT REQUIRED)

add_executable(3ex_rubiks main.cpp)

target_link_libraries(3ex_rubiks PRIVATE
        SFML::Window
        OpenGL::GL
        glm::glm
        ${OPENGL_LIBRARY}
        ${GLUT_LIBRARY}
)

target_link_libraries(3ex_rubiks PRIVATE
        glm::glm
)