cmake_minimum_required(VERSION 3.16) # 
project(408-All)

set(CMAKE_CXX_STANDARD 20)

# 添加子项目
file(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)

foreach(child ${children})
    if (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${child} AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${child}/CMakeLists.txt)
        message(STATUS "Adding subdirectory: ${child}")
        add_subdirectory(${child})
    endif()
endforeach()

