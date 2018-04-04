// Copyright (c) 2018 Roman Putanowicz
//! @brief Define Manager class for managaing application.

#pragma once

#include <string>

namespace v2g 
{

struct FieldDef
{
  std::string name = std::string("data");
  std::string expression = std::string("x");
  FieldDef(const std::string &fieldName, const std::string &fieldExpression) : name(fieldName), expression(fieldExpression){}
  FieldDef() = default;
  // operator= will be used to assign to the FieldDef
  FieldDef& operator=(const std::string &str);
  std::ostream& print(std::ostream &out) const;
};

std::ostream& operator<<(std::ostream &os, const FieldDef &f);

class Manager {
public:
  bool parseCmdArgs(int argc, char *argv[]);

  std::string inFile;
  FieldDef field;
  bool noLog = false;
  bool writeInfo = false;
  int exitStatus = EXIT_SUCCESS;
};

} // namespace v2g
