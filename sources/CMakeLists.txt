cmake_minimum_required(VERSION 3.4)

add_executable(vtk2getfem
  main.cpp
  external/logging/easyloggingpp/easylogging++.cc
)

target_include_directories(vtk2getfem 
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external/cli
    ${CMAKE_CURRENT_SOURCE_DIR}/external/logging/easyloggingpp
)

target_link_libraries(vtk2getfem ${VTK_LIBRARIES})
