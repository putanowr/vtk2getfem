// Copyright (c) 2018 Roman Putanowicz
//! @brief Implement functor object that wrapps global functions.

#include "global_function.h"

#include <stdexcept>

namespace v2g 
{

GlobalFunction::GlobalFunction(const std::string &name, 
                               const std::string &expression) : name_(name)
{
  parser_.DefineVar("x", &pt_[0]);
  parser_.DefineVar("y", &pt_[1]);
  parser_.DefineVar("z", &pt_[2]);
  parser_.SetExpr(expression);
}

double GlobalFunction::at(double x, double y, double z) const
{
  pt_[0] = x;
  pt_[1] = y;
  pt_[2] = z;
  return parser_.Eval();
}

double GlobalFunction::at(size_t ncoords, const double *coords) const
{
  for (size_t i=0; i<ncoords; ++i) pt_[i] = coords[i];
  return parser_.Eval();
}
} // namespace v2g
