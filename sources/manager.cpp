// Copyright (c) 2018 Roman Putanowicz
//! @brief Define Manager class for managaing application.

#include "manager.h"

#include <tclap/CmdLine.h>
#include <easylogging++.h>

namespace v2g 
{

bool Manager::parseCmdArgs(int argc, char *argv[])
{
  auto isOK = true;
  try {
    TCLAP::CmdLine cmd("Convert VTK to GMSH file", ' ', "0.1");
    TCLAP::ValueArg<std::string> outfileArg("o", "outfile", "output file name", false,"v2g.dat","string");
    TCLAP::UnlabeledValueArg<std::string> infileArg("infile", "input file name", true, "", "string");
    TCLAP::SwitchArg meshInfoArg("i", "meshinfo", "print mesh info", false);
    TCLAP::SwitchArg noLogArg("s", "nolog", "switch off log messages", false);
    cmd.add(outfileArg);
    cmd.add(infileArg);
    cmd.add(meshInfoArg);
    cmd.add(noLogArg);
    cmd.parse(argc, argv);

    inFile = infileArg.getValue();
    writeInfo = meshInfoArg.getValue();
    noLog = noLogArg.getValue();

  } catch(TCLAP::ArgException &e) {
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    isOK = false;
    exitStatus = EXIT_FAILURE;
  }
  return isOK;
}

} // namespace v2g
