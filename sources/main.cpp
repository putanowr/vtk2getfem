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
  bool noLog = false;
  bool writeInfo = false;
};

void Config::parseCmdArgs(int argc, char *argv[])
{
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
}

void main_body(const Config &myConfig);
void setup_logging(const Config &myConfig);

int main(int argc, char *argv[]) {
 Config myConfig;
 try {
   myConfig.parseCmdArgs(argc, argv);
  } catch(TCLAP::ArgException &e) {
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
  }
  setup_logging(myConfig);
  main_body(myConfig);
  return EXIT_SUCCESS;
}

void setup_logging(const Config &myConfig)
{
  if (myConfig.noLog) {
    el::Configurations defaultConf;
    defaultConf.setToDefault();
    defaultConf.set(el::Level::Global, el::ConfigurationType::Enabled, std::string("false"));
    el::Loggers::reconfigureLogger("default", defaultConf);
  }
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
