cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_COMPILER "g++")

project(exec LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

link_directories(${CMAKE_SOURCE_DIR}/lib)

file(GLOB SOURCES "src/*.cpp")

add_executable("${PROJECT_NAME}" ${SOURCES})

target_include_directories("${PROJECT_NAME}" PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries("${PROJECT_NAME}" PRIVATE Pcap++ Packet++ Common++ pcap)