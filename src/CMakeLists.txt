cmake_minimum_required(VERSION 3.17)
project(piskworky)

set(CMAKE_CXX_STANDARD 20)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(piskworky main.cpp user_interface.cpp user_interface.h playground.cpp playground.h player.h point.h human_player.cpp human_player.h computer_player.cpp computer_player.h)
target_link_libraries(piskworky ${CURSES_LIBRARIES})
