cmake_minimum_required(VERSION 4.0)

project(vec LANGUAGES C)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(vecparser src/parser.y 
             ${CMAKE_CURRENT_BINARY_DIR}/parser.c
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.h)

FLEX_TARGET(vecscanner src/scanner.l ${CMAKE_CURRENT_BINARY_DIR}/scanner.c)

ADD_FLEX_BISON_DEPENDENCY(vecscanner vecparser)

add_executable(vec
    ${BISON_vecparser_OUTPUTS}
    ${FLEX_vecscanner_OUTPUTS}
    src/main.c
)

target_include_directories(vec PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
