cmake_minimum_required(VERSION 3.10)

project(snake_tests)

set(CMAKE_CXX_STANDARD 17)
include_directories(../snake/snake)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

function(getSources input output)	
    file(GLOB SRC_LIST ${input}/*.cpp ${input}/*/*.cpp)	
    SET(listVar "")	
    foreach(currentFile ${SRC_LIST})	
        if (${currentFile} MATCHES "/main.cpp")	
        else()	
            LIST(APPEND listVar ${currentFile})	
        endif ()	
    endforeach()	
    set(${output} ${listVar} PARENT_SCOPE)	
endfunction(getSources)

getSources(../snake/snake/ SRC_LIST)
file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/snake/*/*.h)
#message(STATUS ${SRC_LIST})

add_executable(${PROJECT_NAME} ${HEADERS} ${SRC_LIST} tests.cpp)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS_GTEST})