project(ion)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11")
aux_source_directory(. SRC_LIST)
aux_source_directory(./ast SRC_LIST)
set(HEADERS utf8string.h token.h ast/visitor.h ast/node.h ast/statement.h ast/expression.h)
add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEADERS})

