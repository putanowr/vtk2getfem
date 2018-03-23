cmake_minimum_required(VERSION 3.4)

project(vtk2getfem)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(VTK REQUIRED NO_MODULE)
include(${VTK_USE_FILE})

add_executable(vtk2getfem main.cpp)

target_include_directories(vtk2getfem 
  PRIVATE
    ${PROJECT_SOURCE_DIR}/cli
)

target_link_libraries(vtk2getfem ${VTK_LIBRARIES})
