cmake_minimum_required(VERSION 3.10)

project(SmartHomeScada)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB SOURCES "src/*.cpp" "${CMAKE_SOURCE_DIR}/main.cpp")

add_executable(SmartHomeScada ${SOURCES})