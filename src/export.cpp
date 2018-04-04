// Copyright (c) 2018 Roman Putanowicz
//! @brief Display short infor about the grid.

#include <easylogging++.h>
#include <getfem/getfem_export.h>

#include "export.h"
#include "manager.h"
#include "model.h"

namespace v2g 
{

void exportData(const Manager &myManager, const getfem::mesh &mesh)
{
  LOG(INFO) << "Exporting mesh" << std::endl;
  auto exporter = getfem::vtk_export("out.vtk", true);
  exporter.exporting(mesh);
  exporter.write_mesh();
}

void exportData(const Manager &myManager, const Model &model)
{
  auto fieldName = std::string("data");
  LOG(INFO) << "Exporting model" << std::endl;
  auto exporter = getfem::vtk_export("out.vtk", true);
  auto fem = model.getFem(fieldName);
  exporter.exporting(fem);
  exporter.write_point_data(fem, model.getDOFs(fieldName), fieldName);
}

} // namespace v2g
