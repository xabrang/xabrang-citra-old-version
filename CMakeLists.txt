cmake_minimum_required(VERSION 3.17)
project(citra)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)

set(SOURCES ${PROJECT_SOURCE_DIR}/src/citra.c)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

file(COPY ${PROJECT_SOURCE_DIR}/src/index.html DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
