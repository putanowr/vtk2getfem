cmake_minimum_required(VERSION 3.4)

project(vtk2getfem)

# Set path for CMake dependencies
IF(NOT DEFINED CMAKE_MODULE_PATH)
  # This block is executed only if this project is configuread as stand alone
  # that is not as a subproject of 'femdk' project
  SET(CMAKE_MODULE_PATH 
      "${CMAKE_SOURCE_DIR}/config/cmake_modules/" 
      CACHE PATH "Path to MorphBar configuration directory")
ENDIF(NOT DEFINED CMAKE_MODULE_PATH)

set (CMAKE_CXX_STANDARD 11)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(VTK REQUIRED NO_MODULE)
find_package(GetFEM REQUIRED)

include(${VTK_USE_FILE})

enable_testing()

add_subdirectory(sources)
add_subdirectory(tests)
add_subdirectory(docs)
