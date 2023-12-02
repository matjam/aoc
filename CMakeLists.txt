# CMakeList.txt : CMake project for aoc-cmake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)


# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

include_directories(
        ${PROJECT_SOURCE_DIR}/src
)

file(GLOB all_SRCS
        "src/*.h"
        "src/*.hpp"
        "src/*.cpp"
        "src/*.c"
        "src/2023/day2/*.cpp"
        "src/2023/day2/*.hpp"
        )

project ("aoc")

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

# Add source to this project's executable.
add_executable(aoc ${all_SRCS})
target_link_libraries(aoc PRIVATE sfml-system sfml-network sfml-graphics sfml-window sfml-main)
set_property(TARGET aoc PROPERTY CXX_STANDARD 20)

# TODO: Add tests and install targets if needed.
