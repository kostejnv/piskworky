cmake_minimum_required(VERSION 3.16.3)
project(piskworky)

set(CMAKE_CXX_STANDARD 20)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(piskworky src/main.cpp src/user_interface.cpp src/user_interface.h src/playground.cpp src/playground.h src/player.h src/point.h src/human_player.cpp src/human_player.h src/computer_player.cpp src/computer_player.h)
target_link_libraries(piskworky ${CURSES_LIBRARIES})
