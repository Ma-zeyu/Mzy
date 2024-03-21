cmake_minimum_required(VERSION 2.8)

PROJECT(serial_test)
SET(CMAKE_CXX_STANDARD 11)
INCLUDE_DIRECTORIES(./include)

ADD_EXECUTABLE(serial_write src/serial_write.cpp)
ADD_EXECUTABLE(serial_read src/serial_read.cpp)
#TARGET_LINK_LIBRARIES(${PROJECT_NAME})
