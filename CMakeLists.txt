cmake_minimum_required(VERSION 3.7)
project(json)

set(CMAKE_CXX_STANDARD  14)
set(YACC_FILE json.tab.cpp)
file(GLOB FILES *.hpp *.h)
set(SOURCE_FILES test.cpp json.tab.cpp json_ast.hpp json_ast.cpp)
add_executable(json ${SOURCE_FILES} ${FILES})