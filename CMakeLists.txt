cmake_minimum_required(VERSION 3.8)
project(LocalHost)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

find_package(Boost REQUIRED)
find_package(imgui REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED) 

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
	${Boost_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME} PUBLIC 
	${Boost_LIBRARIES}	
	${OPENGL_LIBRARIES}
	glfw
	imgui::imgui
)
target_compile_definitions(${PROJECT_NAME} PRIVATE _WIN32_WINNT=0x0601)