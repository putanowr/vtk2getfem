// Copyright (c) 2018 Roman Putanowicz
//! @brief Simple model of discretised global field.

#include "global_function.h"
#include "model.h"

#include <getfem/getfem_interpolation.h>

namespace v2g 
{

Model::Model() : fem_(mesh_)
{
  fem_.set_classical_finite_element(1);
}

void Model::interpolate(const GlobalFunction &fun)
{
  auto name = fun.name();
  if (!model_.variable_exists(name))
  {
    model_.add_fem_variable(name, fem_); 
  }
  getfem::interpolation_function(fem_, model_.real_variable(name), fun);
}

} // namespace v2g
