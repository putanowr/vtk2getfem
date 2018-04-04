// Copyright (c) 2018 Roman Putanowicz
//! @brief Define Manager class for managaing application.

#include "manager.h"

#include <tclap/CmdLine.h>
#include <easylogging++.h>
#include <string>

namespace v2g
{

FieldDef& FieldDef::operator=(const std::string &str)
{
  auto delim = std::string("=");
  auto start = 0U;
  auto end = str.find(delim);
  if (end != std::string::npos)
  {
    name = str.substr(start, end - start);
    start = end+1;
    end = str.size();
    expression = str.substr(start, end-start);
  }
  else
  {
    throw TCLAP::ArgParseException(str + " : missing equal sign in file specification");
  }
  return *this;
}

std::ostream& FieldDef::print(std::ostream &out) const
{
  out << "\"" << name << "=" << expression << "\"";
  return out;
}

std::ostream& operator<<(std::ostream &os, const FieldDef &f)
{
    return f.print(os);
}

} // namespace v2g

namespace TCLAP
{

template<>
struct ArgTraits<v2g::FieldDef> {
    typedef StringLike ValueCategory;
};

} // namespace TCLAP

namespace v2g
{

bool Manager::parseCmdArgs(int argc, char *argv[])
{
  auto isOK = true;
  try {
    TCLAP::CmdLine cmd("Convert VTK to GMSH file", ' ', "0.1");
    TCLAP::ValueArg<std::string> outfileArg("o", "outfile", "output file name", false,"v2g.dat","string", cmd);
    TCLAP::MultiArg<FieldDef>     fieldArg("f", "field", "field", false, "FieldDef", cmd);
    TCLAP::UnlabeledValueArg<std::string> infileArg("infile", "input file name", true, "", "string", cmd);
    TCLAP::SwitchArg meshInfoArg("i", "meshinfo", "print mesh info", cmd, false);
    TCLAP::SwitchArg noLogArg("s", "nolog", "switch off log messages",cmd,  false);
    cmd.parse(argc, argv);

    inFile = infileArg.getValue();
    writeInfo = meshInfoArg.getValue();
    noLog = noLogArg.getValue();
    fields = fieldArg.getValue();

  } catch(TCLAP::ArgException &e) {
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    isOK = false;
    exitStatus = EXIT_FAILURE;
  }
  return isOK;
}

} // namespace v2g


