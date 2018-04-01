// Copyright (c) 2018 Roman Putanowicz
//! @brief Implement functor object that wrapps global functions.

#pragma once

#include <stdlib.h>

namespace v2g 
{
class GlobalFunction
{
public:
  GlobalFunction();
  double at(double x, double y, double z) const;
  double at(size_t ncoords, const double *coords) const;
  template <class T>
  double operator ()(const T &point) const
  {
    return at(point.size(), &(point[0]));
  }
};
} // namespace v2g
