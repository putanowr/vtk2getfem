cmake_minimum_required(VERSION 3.4)

project(vtk2getfem)

add_executable(vtk2getfem main.cpp)

target_include_directories(vtk2getfem 
  PRIVATE
    ${PROJECT_SOURCE_DIR}/cli
)
