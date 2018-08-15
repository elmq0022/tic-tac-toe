cmake_minimum_required(VERSION 3.10)
project(tic_tac_toe)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# find SDL2 and SDL2_image
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
add_executable(Exe src/main.cpp)

target_link_libraries(Exe ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY})

# set warning levels for clang and gcc
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")


# Set an output directory for our binaries
set(BIN_DIR ${tic_tac_toe_SOURCE_DIR}/bin)
install(TARGETS Exe RUNTIME DESTINATION ${BIN_DIR})
