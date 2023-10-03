cmake_minimum_required(VERSION 3.12)
project(Network)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

find_package(Boost REQUIRED)

add_library(${PROJECT_NAME} SHARED 
	network.hpp
	network.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PUBLIC _WIN32_WINNT=0x0601)
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR})
install(FILES network.hpp DESTINATION ${CMAKE_SOURCE_DIR}/include)