cmake_minimum_required(VERSION 3.0)

add_library(${PROJECT_NAME} SHARED
	StringStack.cpp 	../api/StringStack.hpp
	Option.cpp			../api/Option.hpp
	ArgumentScanner.cpp ../api/ArgumentScanner.hpp
	OptionScanner.cpp	../api/OptionScanner.hpp
	OptionEqScanner.cpp ../api/OptionEqScanner.hpp
	OptionSpScanner.cpp	../api/OptionSpScanner.hpp)

target_include_directories(${PROJECT_NAME} PUBLIC ../api/)

install(TARGETS ${PROJECT_NAME}
	LIBRARY
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
