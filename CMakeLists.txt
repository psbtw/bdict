cmake_minimum_required(VERSION 3.28)

project(bdict)

# configure_file (
#   "${PROJECT_SOURCE_DIR}/config.h.in"
#   "${PROJECT_BINARY_DIR}/config.h"
# )

set(CMAKE_CXX_STANDARD "14")
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -fsanitize=address")
#set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")


set(COMMON_ROOT_DIR ${PROJECT_SOURCE_DIR}/../bcommon)

include_directories(${COMMON_ROOT_DIR}/common ${COMMON_ROOT_DIR}/container)
file(GLOB COMMON_SRC ${COMMON_ROOT_DIR}/common/log/log.c ${COMMON_ROOT_DIR}/common/log/log.h
    ${COMMON_ROOT_DIR}/common/*.cpp ${COMMON_ROOT_DIR}/common/*.hpp
    ${COMMON_ROOT_DIR}/container/*.cpp ${COMMON_ROOT_DIR}/container/*.hpp)

message(Debug "common src: ${COMMON_SRC}")
file(GLOB SRC ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/*.hpp 
    ${PROJECT_SOURCE_DIR}/pinyinEncoder/*.cpp ${PROJECT_SOURCE_DIR}/pinyinEncoder/*.hpp)
message(Debug "bdict src: ${SRC}")
add_executable(a.out ${SRC} ${COMMON_SRC})
add_library(${PROJECT_NAME} ${SRC} ${COMMON_SRC})

#target_link_libraries(nqueen common)