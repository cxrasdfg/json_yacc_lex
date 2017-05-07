cmake_minimum_required(VERSION 3.7)
project(json)

set(CMAKE_CXX_STANDARD  14)
set(YACC_FILE json.tab.cpp)
file(GLOB FILES *.hpp *.h)
set(SOURCE_FILES test.cpp )
add_executable(json ${SOURCE_FILES})
target_link_libraries(json /home/theppsh/ClionProjects/cpp/json/cmake-build-release/libjson.a)