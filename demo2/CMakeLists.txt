cmake_minimum_required(VERSION 3.22...3.33)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

project(program
    VERSION 0.1.0
    DESCRIPTION "learn cg, try to display triangle"
    LANGUAGES C
)

include(CTest)
enable_testing()

include_directories("/usr/local/include")

if (IS_DIRECTORY "/usr/include/GLFW")
    message(VERBOSE " GLFW was installed by apt, then gcc will use -lglfw instead of -lglfw3")
    include_directories("/usr/include/GLFW")
else()
    include_directories("/usr/local/include/GLFW")
endif()

# all .c files
aux_source_directory(. DIR_SRCS)
aux_source_directory(../3rd DIR_SRCS)
add_executable(program ${DIR_SRCS})

if (IS_DIRECTORY "/usr/include/GLFW")
    target_link_libraries(${PROJECT_NAME} -lglfw3 -lm)
else()
    target_link_libraries(${PROJECT_NAME} -lglfw3 -lm)   
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)