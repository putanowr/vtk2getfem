#include <iostream>
#include <stdlib.h>

#include <tclap/CmdLine.h>
#include <easylogging++.h>

#include <vtkUnstructuredGrid.h> 
#include <vtkUnstructuredGridReader.h>
#include <vtkSmartPointer.h>

#include <vtk2getfem.h>

INITIALIZE_EASYLOGGINGPP

void main_body(const std::string &inFile);

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

    main_body(infileArg.getValue());

  } catch(TCLAP::ArgException &e) {
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
  }

  return EXIT_SUCCESS;
}

void main_body(const std::string &inFile) {
  using MyGridPtr = vtkSmartPointer<vtkUnstructuredGrid>;
  vtkUnstructuredGridReader *reader = vtkUnstructuredGridReader::New();
  reader->SetFileName(inFile.c_str());
  reader->Update();
  vtkSmartPointer<vtkUnstructuredGrid> myGridPtr = reader->GetOutput();

  std::cout << "Number of nodes: " << myGridPtr->GetNumberOfPoints() << std::endl;
  auto mesh = getfem::mesh();
  v2g::copyMesh(myGridPtr, mesh);
  reader->Delete();
}
