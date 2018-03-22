#include <iostream>
#include <stdlib.h>
#include <tclap/CmdLine.h>

int main(int argc, char *argv[]) {
  try {
    TCLAP::CmdLine cmd("Convert VTK to GMSH file", ' ', "0.1");
    TCLAP::ValueArg<std::string> outfileArg("o", "outfile", "output file name", 
                                            false,"v2g.dat","string");
    TCLAP::UnlabeledValueArg<std::string> infileArg("infile", "input file name",
                                            true, "", "string");
    cmd.add(outfileArg);
    cmd.add(infileArg);
    cmd.parse(argc, argv);
  } catch(TCLAP::ArgException &e) {
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
  }
  return EXIT_SUCCESS;
}