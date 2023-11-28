cmake_minimum_required(VERSION 3.20)
project(Adapters) 

set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 23)

find_package(Boost REQUIRED)

add_library(${PROJECT_NAME} SHARED
	write_controller.hpp
	web_write_controller.hpp
	web_write_controller.cxx
	
	deserializer.hpp 
	deserializerimpl.hpp
	deserializerimpl.cxx
	
	serializer.hpp
	serializerimpl.hpp
	serializerimpl.cxx 
	binary_manipulation/binary_extractor.hpp
	binary_manipulation/binary_extractor.cxx)

target_include_directories(${PROJECT_NAME}  
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} 
	PUBLIC ${Boost_LIBRARIES})


install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR})