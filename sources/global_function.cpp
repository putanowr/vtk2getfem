// Copyright (c) 2018 Roman Putanowicz
//! @brief Implement functor object that wrapps global functions.

#include "global_function.h"

#include <stdexcept>

namespace v2g 
{

double GlobalFunction::at(double x, double y, double z) const
{
  return x;
}

double GlobalFunction::at(size_t ncoords, const double *coords) const
{
  if (ncoords == 2)
  {
    return at(coords[0], coords[1], 0.0);
  }
  else if (ncoords == 3)
  {
    return at(coords[0], coords[2], coords[3]);
  }
  else if (ncoords == 1)
  {
    return at(coords[0], 0.0, 0.0);
  }
  else
  {
    throw std::logic_error("Invalid point dimension != 1;2 or 3");
  } 
}
} // namespace v2g
