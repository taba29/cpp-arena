cmake_minimum_required(VERSION 3.20)
project(cpp_arena LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Werror -Wpedantic)

# ccache（あれば）
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()

# Debug で Sanitizer（AppleClang でも動く書き方）
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_options(-fsanitize=address -fsanitize=undefined)
  add_link_options(-fsanitize=address -fsanitize=undefined)
endif()

# デモ4つ（スタブでも可：後で中身を差し替え）
add_executable(day1_smartptr src/day1_smartptr.cpp)
add_executable(day1_move     src/day1_move.cpp)
add_executable(day1_span     src/day1_span.cpp)
add_executable(day1_time     src/day1_time.cpp)

# デモ5つ目
add_executable(day3_physics src/day3_physics.cpp)

add_executable(day5_ai src/day5_ai.cpp)

add_executable(day6_geometry src/day6_geometry.cpp)

add_executable(day7_integration src/day7_integration.cpp)

# ---- CTest を正しく初期化し、tests/ を読む ----
include(CTest)            # => BUILD_TESTING オプションが定義され、既定 ON
if(BUILD_TESTING)
  add_subdirectory(tests) # tests/CMakeLists.txt を取り込む
endif()

