cmake_minimum_required(VERSION 3.28)

project(dict)

# configure_file (
#   "${PROJECT_SOURCE_DIR}/config.h.in"
#   "${PROJECT_BINARY_DIR}/config.h"
# )

set(CMAKE_CXX_STANDARD "20")
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -fsanitize=address")
#set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")



#add_subdirectory(common)

#add_executable(a.out 0-100/45-canJump-2.cc)
file(GLOB SRC ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/*.hpp)
add_executable(a.out ${SRC})

#target_link_libraries(nqueen common)