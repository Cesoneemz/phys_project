cmake_minimum_required(VERSION 2.8)

project(soundrecogniser)
add_executable(${PROJECT_NAME} main.cpp)

option (WITH_DEBUG_UTILS "" ON)
add_subdirectory(include)
if (WITH_DEBUG_UTILS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE WITH_DEBUG_UTILS)
endif (WITH_DEBUG_UTILS)
target_link_libraries(${PROJECT_NAME} openal debug debugging recorder)
