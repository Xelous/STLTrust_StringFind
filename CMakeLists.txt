cmake_minimum_required(VERSION 3.8)

set(PROJECT_NAME STLTrust_StringFind)

project (${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp)
find_package(Threads)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
