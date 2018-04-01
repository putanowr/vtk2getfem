// Copyright (c) 2018 Roman Putanowicz
//! @brief Simple model of discretised global field.

#include "model.h"

namespace v2g 
{

getfem::mesh & Model::getMesh()
{
  return mesh_;
}

} // namespace v2g
