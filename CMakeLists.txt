cmake_minimum_required(VERSION 3.24)
project(THIS_FUCKING_BULLSHIT C)

set(CMAKE_C_STANDARD 99)

add_executable(THIS_FUCKING_BULLSHIT parser.tab.c lex.yy.c ast.c output.c string_utils.c)
