// Copyright (c) 2018 Roman Putanowicz
//! @brief Implement functor object that wrapps global functions.

#pragma once

#include <stdlib.h>

namespace v2g 
{
class GlobalFunction
{
public:
  GlobalFunction() = default;
  double at(double x, double y, double z) const;
  double at(size_t ncoords, const double *coords) const;
  template <typename T>
  double operator ()(const T &point) const
  {
    return at(point[0], point[1], point[2]);
  }
};
} // namespace v2g
