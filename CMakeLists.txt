cmake_minimum_required(VERSION 3.17)
project(piskworky)

set(CMAKE_CXX_STANDARD 20)
add_library(curses STATIC main.cpp console_comunicator.cpp console_comunicator.h playground.cpp playground.h player.h)
add_executable(piskworky main.cpp console_comunicator.cpp console_comunicator.h playground.cpp playground.h player.h point.h)
target_link_libraries(piskworky curses)
