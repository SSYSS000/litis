cmake_minimum_required(VERSION 3.0)

project(libprogargs)

add_executable(libprogargs
	src/main.cpp
	src/ArgumentStack.cpp
	src/Option.cpp
	src/ArgumentScanner.cpp
	api/ArgumentScanner.hpp
	src/OptionScanner.cpp
	api/OptionScanner.hpp
	src/OptionEqScanner.cpp
	api/OptionEqScanner.hpp
	src/OptionSpScanner.cpp
	api/OptionSpScanner.hpp)

target_include_directories(libprogargs PRIVATE api/)

install(TARGETS libprogargs RUNTIME DESTINATION bin)
