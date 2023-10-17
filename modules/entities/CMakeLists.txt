cmake_minimum_required(VERSION 3.20)
project(Entities) 

add_library(${PROJECT_NAME} SHARED 
	entities_api.hpp
	filemanipulator.hpp
	filemanipulatorimpl.hpp
	filemanipulatorimpl.cxx
)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR})