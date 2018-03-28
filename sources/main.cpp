#include <iostream>
#include <stdlib.h>

#include <tclap/CmdLine.h>
#include <easylogging++.h>

#include <vtkUnstructuredGrid.h> 
#include <vtkUnstructuredGridReader.h>
#include <vtkSmartPointer.h>

#include "vtk2getfem.h"
#include "info.h" 

INITIALIZE_EASYLOGGINGPP

class Config {
public:
  void parseCmdArgs(int argc, char *argv[]);

  std::string inFile;
  bool writeInfo = false;
};

void Config::parseCmdArgs(int argc, char *argv[])
{
  TCLAP::CmdLine cmd("Convert VTK to GMSH file", ' ', "0.1");
  TCLAP::ValueArg<std::string> outfileArg("o", "outfile", "output file name", false,"v2g.dat","string");
  TCLAP::UnlabeledValueArg<std::string> infileArg("infile", "input file name", true, "", "string");
  TCLAP::SwitchArg meshInfoArg("i", "meshinfo", "print mesh info", false);
  cmd.add(outfileArg);
  cmd.add(infileArg);
  cmd.add(meshInfoArg);
  cmd.parse(argc, argv);

  inFile = infileArg.getValue();
  writeInfo = meshInfoArg.getValue();
}

void main_body(const Config &myConfig);

int main(int argc, char *argv[]) {
 Config myConfig;
 try {
   myConfig.parseCmdArgs(argc, argv);
  } catch(TCLAP::ArgException &e) {
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
  }

  main_body(myConfig);
  return EXIT_SUCCESS;
}

void main_body(const Config &myConfig) {
  using MyGridPtr = vtkSmartPointer<vtkUnstructuredGrid>;
  vtkUnstructuredGridReader *reader = vtkUnstructuredGridReader::New();
  reader->SetFileName(myConfig.inFile.c_str());
  reader->Update();
  vtkSmartPointer<vtkUnstructuredGrid> myGridPtr = reader->GetOutput();

  if (myConfig.writeInfo) {
    v2g::writeInfo(std::cout, myGridPtr);
  }

  auto mesh = getfem::mesh();
  v2g::copyMesh(myGridPtr, mesh);
  reader->Delete();
}
