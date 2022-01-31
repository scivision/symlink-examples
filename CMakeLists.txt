cmake_minimum_required(VERSION 3.19...3.22)

project(SymlinkDemo LANGUAGES C CXX)

enable_testing()

# Check C++17 compiler
include(CheckIncludeFileCXX)
include(CheckCXXSymbolExists)

if(MSVC)
  set(CMAKE_REQUIRED_FLAGS /std:c++17)
else()
  set(CMAKE_REQUIRED_FLAGS -std=c++17)
endif()

check_cxx_symbol_exists(__cpp_lib_filesystem filesystem HAVE_CXX17_FILESYSTEM)
if(NOT HAVE_CXX17_FILESYSTEM)
  check_include_file_cxx(experimental/filesystem HAVE_CXX17_EXPERIMENTAL_FILESYSTEM)
endif()

# C++ example

if(HAVE_CXX17_FILESYSTEM OR HAVE_CXX17_EXPERIMENTAL_FILESYSTEM)
  add_executable(check_symlink check_symlink.cpp)
  target_compile_features(check_symlink PRIVATE cxx_std_17)

  add_test(NAME C++symlink COMMAND check_symlink)
  set_tests_properties(C++symlink PROPERTIES
  SKIP_RETURN_CODE 77
  TIMEOUT 5
  )
endif()

find_package(Python 3.8...4 COMPONENTS Interpreter)

if(Python_Interpreter_FOUND)
  find_program(pytest NAMES pytest)
  # assumes pytest affiliated with this python version

  add_test(NAME pytest COMMAND Python::Interpreter -m pytest ${CMAKE_CURRENT_SOURCE_DIR})
  set_tests_properties(pytest PROPERTIES DISABLED $<NOT:$<BOOL:${pytest}>>)
endif()
