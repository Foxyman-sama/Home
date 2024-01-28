cmake_minimum_required(VERSION 3.20)
project(Home)

option(Testing "Tests" TRUE)
configure_file(config.h.in config.h)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

find_package(Boost REQUIRED)

file(GLOB_RECURSE src modules/*.cxx)

add_executable(${PROJECT_NAME} 
	main.cxx
	${src})
target_include_directories(${PROJECT_NAME} PRIVATE
	modules/core
	modules/webserver
	${CMAKE_BINARY_DIR}
	${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})  

if (Testing)
	enable_testing()
	add_subdirectory(test)
	target_link_libraries(${PROJECT_NAME} PUBLIC Tests)
	add_test(runUnitTests ${PROJECT_NAME})
endif()