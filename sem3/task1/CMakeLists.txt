cmake_minimum_required(VERSION 3.10)

project(geometry CXX)

set(APPNAME_TASK ${PROJECT_NAME}_task)
set(APPNAME_TASK_SELFTEST ${PROJECT_NAME}_task_selftest)

set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

include_directories(${PROJECT_SOURCE_DIR}/inc)

add_executable(${APPNAME_TASK} ${PROJECT_SOURCE_DIR}/src/task.cpp)
add_executable(${APPNAME_TASK_SELFTEST} ${PROJECT_SOURCE_DIR}/src/task.cpp)

target_compile_definitions(${APPNAME_TASK_SELFTEST} PRIVATE -DSELFTEST)
target_compile_options(${APPNAME_TASK_SELFTEST} PRIVATE -g --coverage)
target_link_libraries(${APPNAME_TASK_SELFTEST} PRIVATE gcov)

add_custom_command(TARGET ${APPNAME_TASK_SELFTEST} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/test ${OUTPUT_DIR}/test)
