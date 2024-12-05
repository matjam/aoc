# CMakeList.txt : CMake project for aoc-cmake, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.13)

# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

file(GLOB all_SRCS
  "src/util/*.hpp"
  "src/*.h"
  "src/*.hpp"
  "src/*.cpp"
  "src/*.c"
  "src/2023/*/*.cpp"
  "src/2023/*/*.hpp"
)

project("aoc")
set(CMAKE_BUILD_TYPE Debug)

# Boost settings
set(Boost_USE_STATIC_LIBS ON) # only find static libs
set(Boost_USE_DEBUG_LIBS OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS ON) # only find release libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON) # link Boost Static libraries

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(Boost REQUIRED)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

# Add source to this project's executable.
add_executable(aoc ${all_SRCS})
target_include_directories(aoc PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src" "${CMAKE_CURRENT_LIST_DIR}/src/util")
target_link_libraries(aoc PRIVATE sfml-system sfml-network sfml-graphics sfml-window fmt::fmt)
set_property(TARGET aoc PROPERTY CXX_STANDARD 23)

# TODO: Add tests and install targets if needed.
