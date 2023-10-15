cmake_minimum_required(VERSION 3.22...3.33)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

project(program 
    VERSION 0.1.0
    DESCRIPTION "learn cg use opengl"
    LANGUAGES C
)

include(CTest)
enable_testing()

include_directories("/usr/local/include")
# removing prefix "GLFW/", so 'glad.h' can rank in front of 'glfw' automatically
include_directories("/usr/local/include/GLFW")

# all .c files
aux_source_directory(. DIR_SRCS)
add_executable(program ${DIR_SRCS})
target_link_libraries(${PROJECT_NAME}
    -lglfw3
    -lm   # -lm need behind glfw3, glfw3 want powf(), 
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)