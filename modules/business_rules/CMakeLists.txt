cmake_minimum_required(VERSION 3.20)
project(BusinessRules) 

add_library(${PROJECT_NAME} SHARED 
	business_rules_api.hpp
	entities/filemanipulator.hpp
	entities/filemanipulatorimpl.hpp
	entities/filemanipulatorimpl.cxx
	interactor/ioboundary.hpp
	interactor/interactor.hpp
	interactor/interactor.cxx
)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR})