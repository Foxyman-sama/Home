cmake_minimum_required(VERSION 3.20)
project(Tests)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

find_package(GTest REQUIRED)
find_package(Boost REQUIRED)

add_library(${PROJECT_NAME} tests.cxx)
target_include_directories(${PROJECT_NAME} PUBLIC 
	tests
	${GTEST_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC
	GTest::gmock_main
	${GTEST_LIBRARIES}
	${Boost_LIBRARIES})