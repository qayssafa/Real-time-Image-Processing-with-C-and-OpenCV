cmake_minimum_required(VERSION 2.8)
project( TaskTwoOpenCV )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( TaskTwoOpenCV TaskTwoOpenCV.cpp
        Camera.cpp
        Camera.h)
target_link_libraries( TaskTwoOpenCV ${OpenCV_LIBS} )
