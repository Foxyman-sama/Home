cmake_minimum_required(VERSION 3.8)
project(LocalHost)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE sources
	include/*.hpp
	src/*.cpp
)

add_executable(${PROJECT_NAME}
	main.cpp
	${sources}
)
target_include_directories(${PROJECT_NAME} PRIVATE
	include
)
target_link_libraries(${PROJECT_NAME} PUBLIC
	NetworkSocket
)

add_subdirectory(libs/NetworkSocket)