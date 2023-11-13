cmake_minimum_required(VERSION 3.20)
project(BusinessRules) 

set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 23)

add_library(${PROJECT_NAME} SHARED 
	business_rules_api.hpp

	entities/entities.hpp
	entities/entities.cxx

	interactor/boundary.hpp
	interactor/definitions.hpp
	interactor/interactor.hpp
	interactor/interactor.cxx)
	
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR})