# Velho @ 2014
# project mellu-proto

cmake_minimum_required(VERSION 2.8)
project(mellu-proto)

if(UNIX)
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
endif(UNIX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

set(Boost_USE_STATIC_LIBS ON)

# TODO Add different components this project requires.
find_package(Boost REQUIRED system program_options filesystem)
find_package(SFML 2 REQUIRED graphics window system)
find_package(Sqlite3 REQUIRED) # Find Sqlite3, used for custom fileformat.

# Inlcude directories
include_directories(${Sqlite3_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${SFML_INCLUDE_DIR})

#message("Boost LIB_DIR : ${Boost_LIBRARY_DIR}")
#message("Boost LIBRARIES : ${Boost_LIBRARIES}")

# Add source directory.
add_subdirectory(src)

add_executable(mellu-proto ${SRC_LIST})
target_link_libraries(mellu-proto
    ${Boost_LIBRARIES} ${SFML_LIBRARIES} ${Sqlite3_LIBRARY})

# Copy the data directory into build directory.
file(COPY data DESTINATION ${CMAKE_BINARY_DIR})
