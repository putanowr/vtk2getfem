// Copyright (c) 2018 Roman Putanowicz
//! @brief Define Manager class for managaing application.

#pragma once

#include <string>

namespace v2g 
{

class Manager {
public:
  bool parseCmdArgs(int argc, char *argv[]);

  std::string inFile;
  bool noLog = false;
  bool writeInfo = false;
  int exitStatus = EXIT_SUCCESS;
};

} // namespace v2g
