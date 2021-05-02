cmake_minimum_required(VERSION 3.20.1)
project(triv_linked_list VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/703bd9caab50b139428cea1aaff9974ebee5742e.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  linked_list_tests
  linked_list_tests.cpp
)
target_link_libraries(
  linked_list_tests
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(linked_list_tests)
