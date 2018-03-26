// Copyright (c) 2018 Roman Putanowicz
//! @brief Function to transfer data from VTK to GetFEM.

#ifndef VTK2GETFEM_H
#define VTK2GETFEM_H

#include <vtkSmartPointer>
#include <vtkUnstructuredGrid>
#include <getfem/getfem_mesh.h>

namespace v2g {
  void copyMesh(vtkSmartPointer<vtkUnstructuredGrid> vtkGrid, 
                getfem::mesh & gmesh);
}

#endif /* !VTK2GETFEM_H */

