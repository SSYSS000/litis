cmake_minimum_required(VERSION 3.0)

project(libprogargs)

add_executable(libprogargs main.cpp)

install(TARGETS libprogargs RUNTIME DESTINATION bin)
