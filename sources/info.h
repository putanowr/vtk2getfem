// Copyright (c) 2018 Roman Putanowicz
//! @brief Display short infor about the grid.

#pragma once

#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <iostream>

namespace v2g 
{

void writeInfo(std::ostream &out, vtkSmartPointer<vtkUnstructuredGrid> vtkGrid);

} // namespace v2g
