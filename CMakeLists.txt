cmake_minimum_required(VERSION 3.10.0)

project(Homework CXX)
set(CMAKE_CXX_STANDARD 17)
include(cmake/StandardProjectSettings.cmake)
# Link this 'library' to set the c++ standard / compile-time options requested
add_library(default INTERFACE)
target_compile_features(default INTERFACE cxx_std_17)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(default)

enable_testing()
add_subdirectory(external/doctest)
include(external/doctest/doctest.cmake)
add_subdirectory(external/standardese EXCLUDE_FROM_ALL)
set(STANDARDESE_TOOL standardese_tool)
find_package(standardese REQUIRED HINTS external/standardese)
add_subdirectory(src)

find_package(Doxygen)
set(DOXYGEN_GENERATE_TREEVIEW YES)
set(DOXYGEN_GENERATE_XML YES)
set(DOXYGEN_HTML_EXTRA_STYLESHEET doxygen-awesome.css)
doxygen_add_docs(doc src docs/index.md COMMENT "Generates all documentation")

add_custom_command(
  TARGET doc
  POST_BUILD
  COMMAND sphinx-build -b html ${CMAKE_CURRENT_LIST_DIR}/docs
          ${CMAKE_CURRENT_BINARY_DIR}/sphinx
          -Dbreathe_projects.example=${CMAKE_CURRENT_BINARY_DIR}/xml
  COMMENT "Generates sphinx documentation")

# add_custom_target(doc2 ALL COMMAND standardese_tool src)
# generates a custom target that will run standardese to generate the documentation
standardese_generate(proj CONFIG standardese.ini
                     INPUT src/lib.hpp)
