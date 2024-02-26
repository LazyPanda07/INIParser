cmake_minimum_required(VERSION 3.27.0)

set(CMAKE_CXX_STANDARD 20)
set(DLL ${CMAKE_SOURCE_DIR}/../INIParser)

if (UNIX)
	set(DLL ${DLL}/lib/libINIParser.so)

	add_definitions(-D__LINUX__)
else ()
	set(DLL ${DLL}/dll/INIParser.dll)
endif (UNIX)

if (EXISTS ${DLL})
	add_definitions(-DINI_PARSER_DLL)

	install(FILES ${DLL} DESTINATION ${CMAKE_BINARY_DIR}/bin)
endif ()

project(Tests)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(
	${PROJECT_NAME} PUBLIC
    ../src/
	gtest/include/
)

target_link_directories(
	${PROJECT_NAME} PUBLIC
	../INIParser/lib
	gtest/lib
)

target_link_libraries(
	${PROJECT_NAME} PUBLIC
    INIParser
	gtest
    gtest_main
)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR}/bin)
