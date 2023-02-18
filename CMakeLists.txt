cmake_minimum_required(VERSION 3.22)
project(matrix_style_terminal)

set(CMAKE_CXX_STANDARD 17)

find_package( Curses REQUIRED )
include_directories( ${CURSES_INCLUDE_DIR} )

add_executable(matrix_style_terminal main.cpp ui.cpp ui.h matrix.cpp matrix.h)

target_link_libraries( matrix_style_terminal ${CURSES_LIBRARIES} )