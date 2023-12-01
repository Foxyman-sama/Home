cmake_minimum_required(VERSION 3.20)
project(Adapters) 

set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 23)

find_package(Boost REQUIRED)

add_library(${PROJECT_NAME} SHARED
	web_write_controller.cxx
	deserializerimpl.cxx
	serializerimpl.cxx 
	binary_manipulation/binary_extractor.cxx)

target_include_directories(${PROJECT_NAME}  
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} 
	PUBLIC ${Boost_LIBRARIES})


install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR})