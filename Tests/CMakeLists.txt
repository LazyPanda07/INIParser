cmake_minimum_required(VERSION 3.27.0)

set(CMAKE_CXX_STANDARD 20)

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
