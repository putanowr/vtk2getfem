// Copyright (c) 2018 Roman Putanowicz
//! @brief Display short infor about the grid.

#include <info.h>

namespace v2g 
{

void writeInfo(std::ostream &out, vtkSmartPointer<vtkUnstructuredGrid> vtkGridPtr)
{
  out << "Number of nodes: " << vtkGridPtr->GetNumberOfPoints() << std::endl;
}

} // namespace v2g
