cmake_minimum_required(VERSION 3.20)
project(Adapters) 

set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 23)

add_library(${PROJECT_NAME} SHARED 
	adapters_api.hpp
	controller.hpp
	webcontroller.hpp
	webcontroller.cxx
	json.hpp
	jsonconverter.hpp)
	
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR})