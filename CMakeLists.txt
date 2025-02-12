project(bdict)

cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -fsanitize=address")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")


set(COMMON_ROOT_DIR ${PROJECT_SOURCE_DIR}/../bcommon)

include_directories(${COMMON_ROOT_DIR}/common ${COMMON_ROOT_DIR}/container)
file(GLOB COMMON_SRC ${COMMON_ROOT_DIR}/common/log/log.c ${COMMON_ROOT_DIR}/common/log/log.h
    ${COMMON_ROOT_DIR}/common/*.cpp ${COMMON_ROOT_DIR}/common/*.hpp
    ${COMMON_ROOT_DIR}/container/*.cpp ${COMMON_ROOT_DIR}/container/*.hpp)

#set(BCOMMON_SRC ${COMMON_SRC} CACHE INTERNAL "bcommon src")

message(Debug "common src: ${COMMON_SRC}")
file(GLOB SRC ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/*.hpp 
    ${PROJECT_SOURCE_DIR}/pinyinEncoder/*.cpp ${PROJECT_SOURCE_DIR}/pinyinEncoder/*.hpp)
message(Debug "bdict src: ${SRC}")
#set(BDICT_SRC ${SRC} CACHE INTERNAL "bdict src")

add_executable(a.out ${SRC} ${COMMON_SRC})
message(Debug "project_name: ${PROJECT_NAME}")
add_library(${PROJECT_NAME} SHARED ${SRC} ${COMMON_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_NAME})

# 指定 bdict 的输出目录
set_target_properties(bdict PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../lib/${ANDROID_ABI}/
)
