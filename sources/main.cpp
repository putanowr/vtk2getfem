#include <iostream>
#include <stdlib.h>

#include <easylogging++.h>


#include <vtkUnstructuredGrid.h> 
#include <vtkUnstructuredGridReader.h>
#include <vtkSmartPointer.h>

#include "export.h"
#include "info.h" 
#include "manager.h"
#include "vtk2getfem.h"

INITIALIZE_EASYLOGGINGPP

void main_body(const v2g::Manager &myManager);
void setup_logging(const v2g::Manager &myManager);

int main(int argc, char *argv[])
{
 v2g::Manager myManager;
 if (myManager.parseCmdArgs(argc, argv))
 {
   setup_logging(myManager);
   main_body(myManager);
 }
 return myManager.exitStatus;
}

void setup_logging(const v2g::Manager &myManager)
{
  if (myManager.noLog) {
    el::Configurations defaultConf;
    defaultConf.setToDefault();
    defaultConf.set(el::Level::Global, el::ConfigurationType::Enabled, std::string("false"));
    el::Loggers::reconfigureLogger("default", defaultConf);
  }
}

void main_body(const v2g::Manager &myManager) {
  using MyGridPtr = vtkSmartPointer<vtkUnstructuredGrid>;
  vtkUnstructuredGridReader *reader = vtkUnstructuredGridReader::New();
  reader->SetFileName(myManager.inFile.c_str());
  reader->Update();
  vtkSmartPointer<vtkUnstructuredGrid> myGridPtr = reader->GetOutput();

  if (myManager.writeInfo) {
    v2g::writeInfo(std::cout, myGridPtr);
  }

  auto mesh = getfem::mesh();
  v2g::copyMesh(myGridPtr, mesh);
  v2g::exportMesh(myManager, mesh);
  reader->Delete();
}
