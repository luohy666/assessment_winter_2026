cmake_minimum_required(VERSION 3.16)
project(detector)

find_package(OpenCV REQUIRED)

include_directories(/usr/include/opencv4)

add_executable(main main.cpp)
target_link_libraries(main ${OpenCV_LIBS})