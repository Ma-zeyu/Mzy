cmake_minimum_required(VERSION 3.16)

project(camera)

add_executable(main main.cpp)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

target_include_directories(main PRIVATE ${EIGEN3_INCLUDE_DIR})
target_link_libraries(main PUBLIC ${OpenCV_LIBS})