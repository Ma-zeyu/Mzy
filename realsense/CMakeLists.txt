cmake_minimum_required(VERSION 3.16)
project(test2)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
find_package(realsense2 REQUIRED)

add_executable(test2 main.cpp)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${realsense2_INCLUDE_DIR})

target_link_libraries(test2 ${OpenCV_LIBS})
target_link_libraries(test2 ${realsense2_LIBRARY})

