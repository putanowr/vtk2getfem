// Copyright (c) 2018 Roman Putanowicz
//! @brief Function to transfer data from VTK to GetFEM.

#include <vtk2getfem.h>
#include <easylogging++.h>

namespace v2g 
{

void copyMesh(vtkSmartPointer<vtkUnstructuredGrid> vtkGrid, getfem::mesh & gmesh)
{
  LOG(INFO) << "To be implemented";
}

} // namespace v2g

