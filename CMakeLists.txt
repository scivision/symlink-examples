cmake_minimum_required(VERSION 3.13...3.26)

project(SymlinkDemo LANGUAGES C CXX)

enable_testing()

include(CheckIncludeFileCXX)
include(CheckCXXSymbolExists)

set(CMAKE_CXX_STANDARD 17)

check_cxx_symbol_exists(__cpp_lib_filesystem "filesystem" HAVE_CXX17_FILESYSTEM)

# C++ example

if(HAVE_CXX17_FILESYSTEM)
  add_executable(check_symlink check_symlink.cpp)

  add_test(NAME CppSymlink COMMAND check_symlink)
endif()

find_package(Python COMPONENTS Interpreter)

if(Python_Interpreter_FOUND AND "${Python_VERSION}" VERSION_GREATER_EQUAL 3.8)
  if(NOT DEFINED Pytest_OK)
    execute_process(COMMAND ${Python_EXECUTABLE} -c "import pytest"
    RESULT_VARIABLE ret
    )
    if(ret EQUAL 0)
      set(Pytest_OK true CACHE BOOL "Pytest found")
    else()
      set(Pytest_OK false CACHE BOOL "Pytest not found")
      message(STATUS "Pytest not found: ${ret}")
    endif()
  endif()

  add_test(NAME pytest
  COMMAND Python::Interpreter -m pytest ${CMAKE_CURRENT_SOURCE_DIR})
  set_property(TEST pytest PROPERTY DISABLED $<NOT:$<BOOL:${Pytest_OK}>>)
endif()

file(GENERATE OUTPUT .gitignore CONTENT "*")
