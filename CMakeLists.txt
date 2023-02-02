cmake_minimum_required(VERSION 3.13...3.25)

project(SymlinkDemo LANGUAGES C CXX)

enable_testing()

include(CheckIncludeFileCXX)
include(CheckCXXSymbolExists)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
  set(CMAKE_REQUIRED_FLAGS /std:c++17)
else()
  set(CMAKE_REQUIRED_FLAGS -std=c++17)
endif()

check_cxx_symbol_exists(__cpp_lib_filesystem filesystem HAVE_CXX17_FILESYSTEM)

# C++ example

if(HAVE_CXX17_FILESYSTEM)
  add_executable(check_symlink check_symlink.cpp)

  add_test(NAME CppSymlink COMMAND check_symlink)
  set_property(TEST CppSymlink PROPERTY SKIP_RETURN_CODE 77)
endif()

find_package(Python COMPONENTS Interpreter)

if(Python_Interpreter_FOUND AND "${Python_VERSION}" VERSION_GREATER_EQUAL 3.8)
  execute_process(COMMAND ${Python_EXECUTABLE} -c "import pytest"
  RESULT_VARIABLE ret
  )
  if(NOT ret EQUAL 0)
    message(STATUS "Pytest not found: ${ret}")
  endif()

  add_test(NAME pytest
  COMMAND Python::Interpreter -m pytest ${CMAKE_CURRENT_SOURCE_DIR})
  set_property(TEST pytest PROPERTY DISABLED $<BOOL:${ret}>)
endif()
