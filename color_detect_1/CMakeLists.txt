cmake_minimum_required(VERSION 3.16)

project(camera)

add_executable(main main.cpp)

find_package(OpenCV REQUIRED)
target_link_libraries(main PUBLIC ${OpenCV_LIBS})