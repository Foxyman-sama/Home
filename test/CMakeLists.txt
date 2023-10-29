cmake_minimum_required(VERSION 3.20)
project(Tests)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE files tests/*.hpp)

find_package(GTest REQUIRED)

add_library(${PROJECT_NAME}
	tests.cxx
	tests.hpp
	${files}
)
target_include_directories(${PROJECT_NAME} PUBLIC 
	${GTEST_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}
)
target_link_libraries(${PROJECT_NAME} PUBLIC
	GTest::gmock_main
	${GTEST_LIBRARIES}
)