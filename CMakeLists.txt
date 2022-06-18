cmake_minimum_required(VERSION 3.0)

project(progargs
	LANGUAGES CXX
	VERSION 1.0.0
	DESCRIPTION "A library for handling program arguments.")

add_library(${PROJECT_NAME} SHARED
	src/main.cpp
	src/ArgumentStack.cpp 	api/ArgumentStack.hpp
	src/Option.cpp		api/Option.hpp
	src/ArgumentScanner.cpp api/ArgumentScanner.hpp
	src/OptionScanner.cpp	api/OptionScanner.hpp
	src/OptionEqScanner.cpp api/OptionEqScanner.hpp
	src/OptionSpScanner.cpp	api/OptionSpScanner.hpp)

target_include_directories(${PROJECT_NAME} PUBLIC api/)

install(TARGETS ${PROJECT_NAME}
	LIBRARY
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
