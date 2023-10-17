cmake_minimum_required(VERSION 3.20)
project(HOME)

option(Testing "Tests" ON)
configure_file(config.h.in config.h @ONLY)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME} main.cxx)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC Entities)

add_subdirectory(modules)

if (Testing)
	add_subdirectory(test)
	target_link_libraries(${PROJECT_NAME} PUBLIC Tests)
endif()