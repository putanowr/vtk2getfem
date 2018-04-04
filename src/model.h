// Copyright (c) 2018 Roman Putanowicz
//! @brief Simple model of discretised global field.

#pragma once

#include <getfem/getfem_mesh.h>
#include <getfem/getfem_models.h>
#include <getfem/getfem_mesh_fem.h>

namespace v2g 
{

class GlobalFunction;

class Model
{
public:
  using Vector = getfem::model_real_plain_vector;
  Model();
  getfem::mesh &getMesh() { return mesh_; }
  const getfem::mesh &getMesh() const { return mesh_;}
  const getfem::mesh_fem &getFem(const std::string &name) const { return model_.mesh_fem_of_variable(name); }
  const Vector & getDOFs(const std::string &name) const { return model_.real_variable(name); }
  void interpolate(const GlobalFunction &fun);
  
private:
  getfem::mesh mesh_;
  getfem::mesh_fem fem_;
  getfem::model model_;
};

} // namespace v2g
