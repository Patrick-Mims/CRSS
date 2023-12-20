cmake_minimum_required(VERSION 3.26)

project(main)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(SRC "src")

# disable warnings
add_definitions(-w)

find_package(json-c CONFIG)
find_package(LibXml2 REQUIRED)

include_directories(include)
include_directories(${PROJECT_SOURCE_DIR})
include_directories(/usr/include/libxml2)

add_executable(${PROJECT_NAME} 
    ${SRC}/init.c
    ${SRC}/fetch.c
    ${SRC}/main.c
    )

target_link_libraries(${PROJECT_NAME} -lcurl -lpthread -lxml2 -ljson-c -lpcap) 
