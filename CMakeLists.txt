cmake_minimum_required(VERSION 3.8)
project(HOME)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

find_package(Boost REQUIRED)

file(GLOB_RECURSE sources
	include/*.hpp
	src/*.cpp
)

add_executable(${PROJECT_NAME}
	main.cpp
	${sources}
)
target_link_libraries(${PROJECT_NAME} PUBLIC Network)

add_subdirectory(network)