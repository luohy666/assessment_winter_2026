cmake_minimum_required(VERSION 3.16)
project(assignment0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(A0_REFERENCE "Build reference implementation for A0-09~11" OFF)
option(A0_BUILD_OPTIONAL_09_11 "Build optional problems A0-09~11" OFF)

add_library(a0_lib)

target_include_directories(a0_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (A0_REFERENCE)
  target_sources(a0_lib PRIVATE src/a0_lib_reference.cpp)
  target_compile_definitions(a0_lib PUBLIC RM_A0_REFERENCE=1)
else()
  target_sources(a0_lib PRIVATE src/a0_lib.cpp)
  target_compile_definitions(a0_lib PUBLIC RM_A0_REFERENCE=0)
endif()

add_executable(a0_01_temperature src/a0_01_temperature.cpp)
add_executable(a0_02_leap_year src/a0_02_leap_year.cpp)
add_executable(a0_03_range_sum src/a0_03_range_sum.cpp)
add_executable(a0_04_vowel_count src/a0_04_vowel_count.cpp)
add_executable(a0_05_score_stats src/a0_05_score_stats.cpp)

target_link_libraries(a0_01_temperature PRIVATE a0_lib)
target_link_libraries(a0_02_leap_year PRIVATE a0_lib)
target_link_libraries(a0_03_range_sum PRIVATE a0_lib)
target_link_libraries(a0_04_vowel_count PRIVATE a0_lib)
target_link_libraries(a0_05_score_stats PRIVATE a0_lib)

add_executable(a0_06_bigint src/a0_06_bigint.cpp)
add_executable(a0_07_log_analyzer src/a0_07_log_analyzer.cpp)
add_executable(a0_08_raii_handle src/a0_08_raii_handle.cpp)

target_link_libraries(a0_06_bigint PRIVATE a0_lib)
target_link_libraries(a0_07_log_analyzer PRIVATE a0_lib)
target_link_libraries(a0_08_raii_handle PRIVATE a0_lib)

# Engineering extensions
if (A0_BUILD_OPTIONAL_09_11)
  add_executable(a0_09_text_pipeline src/a0_09_text_pipeline.cpp)
  add_executable(a0_10_rule_engine src/a0_10_rule_engine.cpp)
  add_executable(a0_11_command_dispatcher src/a0_11_command_dispatcher.cpp)

  target_link_libraries(a0_09_text_pipeline PRIVATE a0_lib)
  target_link_libraries(a0_10_rule_engine PRIVATE a0_lib)
  target_link_libraries(a0_11_command_dispatcher PRIVATE a0_lib)
endif()

# Tests (GoogleTest via FetchContent)
include(CTest) # defines BUILD_TESTING
if (BUILD_TESTING)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  enable_testing()
  add_executable(a0_tests tests/a0_tests.cpp)

  target_link_libraries(a0_tests PRIVATE a0_lib GTest::gtest_main)

  include(GoogleTest)
  gtest_discover_tests(a0_tests)
endif()

