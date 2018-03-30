// Copyright (c) 2018 Roman Putanowicz
//! @brief Display short infor about the grid.

#include <easylogging++.h>
#include <getfem/getfem_export.h>

#include "export.h"
#include "manager.h"

namespace v2g 
{

void exportMesh(const Manager &myManager, const getfem::mesh &mesh)
{
  LOG(INFO) << "Exporting mesh" << std::endl;
  auto exporter = getfem::vtk_export("out.vtk", true);
  exporter.exporting(mesh);
  exporter.write_mesh();
}

} // namespace v2g
