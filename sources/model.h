// Copyright (c) 2018 Roman Putanowicz
//! @brief Simple model of discretised global field.

#pragma once

#include <getfem/getfem_mesh.h>
#include <getfem/getfem_models.h>
#include <getfem/getfem_mesh_fem.h>

namespace v2g 
{

class Model
{
public:
  Model() = default;
  getfem::mesh &getMesh();
  
private:
  getfem::mesh mesh_;
  getfem::mesh_fem fem_;
  getfem::model model_;
};

} // namespace v2g
