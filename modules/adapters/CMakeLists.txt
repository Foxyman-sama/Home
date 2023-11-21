cmake_minimum_required(VERSION 3.20)
project(Adapters) 

set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 23)

add_library(${PROJECT_NAME} SHARED
	write_controller.hpp
	web_write_controller.hpp
	web_write_controller.cxx
	
	deserializer.hpp)

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR})