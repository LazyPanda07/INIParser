cmake_minimum_required(VERSION 3.27.0)

set(CMAKE_CXX_STANDARD 20)
set(GTEST_VERSION 1.17.0)
set(DLL ${CMAKE_SOURCE_DIR}/../INIParser)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})

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

include(FetchContent)

FetchContent_Declare(
  gtest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v${GTEST_VERSION}
)

FetchContent_MakeAvailable(gtest)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(
	${PROJECT_NAME} PUBLIC
    ../include/
)

target_link_directories(
	${PROJECT_NAME} PUBLIC
	../INIParser/lib
)

target_link_libraries(
	${PROJECT_NAME} PUBLIC
    INIParser
	gtest
	gtest_main
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
