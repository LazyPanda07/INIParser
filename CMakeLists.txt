cmake_minimum_required(VERSION 3.27.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
option(BUILD_SHARED_LIBS "" OFF)

if (UNIX)
	add_definitions(-D__LINUX__)
endif (UNIX)

if (${BUILD_SHARED_LIBS})
	add_definitions(-DINI_PARSER_DLL)
endif ()

project(INIParser)

add_library(
	${PROJECT_NAME}
	src/INIParser.cpp
)

install(
	TARGETS ${PROJECT_NAME}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/install-dir/lib
	LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/install-dir/lib
	RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/install-dir/dll
)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
	install(DIRECTORY src/ DESTINATION ${CMAKE_INSTALL_PREFIX}/install-dir/include FILES_MATCHING PATTERN "*.h")
endif ()
