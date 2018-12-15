cmake_minimum_required(VERSION 2.8)

project(soundrecognizer_sources)
add_library(recorder STATIC record.cpp)
add_library(recogniser STATIC recognise.cpp)
if (WITH_DEBUG_UTILS)
    include_directories(debug)
    add_subdirectory(debug)
endif (WITH_DEBUG_UTILS)
