cmake_minimum_required(VERSION 3.20)
project(HOME)

option(Testing "Tests" TRUE)
configure_file(config.h.in config.h)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME} main.cxx)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC
	BusinessRules
)

add_subdirectory(modules)

if (Testing)
	enable_testing()
	add_subdirectory(test)
	target_link_libraries(${PROJECT_NAME} PUBLIC Tests)
	add_test(runUnitTests ${PROJECT_NAME})
endif()