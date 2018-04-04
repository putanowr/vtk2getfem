// Copyright (c) 2018 Roman Putanowicz
//! @brief Implement functor object that wrapps global functions.

#pragma once

#include <stdlib.h>
#include <muParser.h>
#include <array>

namespace v2g 
{
class GlobalFunction
{
public:
  GlobalFunction(const std::string &name, const std::string &expression);
  double at(double x, double y, double z) const;
  double at(size_t ncoords, const double *coords) const;
  template <typename T>
  double operator ()(const T &point) const
  {
    pt_[0] = point[0]; 
    pt_[1] = point[1]; 
    pt_[2] = point[2]; 
    return parser_.Eval();
  }
  const std::string name() const {return name_;}
  const std::string expression() const {return parser_.GetExpr();}
private:
  std::string name_;
  mu::Parser parser_;
  mutable std::array<double, 3> pt_ = {0.0, 0.0, 0.0};
};

} // namespace v2g
