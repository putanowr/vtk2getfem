// Copyright (c) 2018 Roman Putanowicz
//! @brief Function to transfer data from VTK to GetFEM.

#include <algorithm>
#include <easylogging++.h>
#include <vtkCellType.h>

#include "vtk2getfem.h"

namespace getfem
{
 struct gf2vtk_dof_mapping : public std::vector<std::vector<unsigned> > {};
 struct gf2vtk_vtk_type : public std::vector<int> {};
 void init_gf2vtk();
}

namespace v2g 
{
static const std::vector<unsigned> &
select_vtk_dof_mapping(unsigned t) {
  getfem::gf2vtk_dof_mapping &vtkmaps = dal::singleton<getfem::gf2vtk_dof_mapping>::instance();
  if (vtkmaps.size() == 0) getfem::init_gf2vtk();
  return vtkmaps[t];
}


class CellMapping {
public:
  CellMapping() = default;
  CellMapping(int cellType);
  void setup(int cellType);
  bgeot::pgeometric_trans getTrans() { return ptrans_; }
  void mapConnectivity(vtkIdType npts, const vtkIdType *pts, std::vector<bgeot::size_type> &ind);
  int vtkCellType() { return vtkCellType_; }
private:
  //! GetFEM geometric transformation corresponding to VTK cell
  bgeot::pgeometric_trans ptrans_ = nullptr;
  //! Integer correcponding to GetFEM mapping between cell indices
  int gmaptype_ = 0;
  //! VTK cell type;
  int vtkCellType_ = -1;
  std::vector<unsigned> map_;
};

CellMapping::CellMapping(int cellType)
{
 setup(cellType);
}

void CellMapping::setup(int cellType)
{
  if (vtkCellType_ == cellType) return;
  vtkCellType_ = cellType;
  switch(vtkCellType_)
  {
    case VTK_LINE: // 3
      ptrans_ = bgeot::simplex_geotrans(1,1);	    
      gmaptype_ = 2;
      break;
    case VTK_TRIANGLE: // 5
      ptrans_  = bgeot::simplex_geotrans(2,1);
      gmaptype_ = 3;
      break;
    case VTK_QUAD: // 9
      ptrans_ = bgeot::parallelepiped_geotrans(2,1);
      gmaptype_ = 5;
      break;
    default:
      throw(std::logic_error("unsupported vtk type"));
  }
  getfem::gf2vtk_dof_mapping &vtkmaps = dal::singleton<getfem::gf2vtk_dof_mapping>::instance();
  if (vtkmaps.size() == 0) getfem::init_gf2vtk();
  map_ = vtkmaps[gmaptype_];
}

void CellMapping::mapConnectivity(vtkIdType npts, const vtkIdType *pts, std::vector<bgeot::size_type> &ind)
{
  ind.resize(npts);
  for (int i=0; i<npts; ++i)
  {
    ind[i] = pts[map_[i]];
  }
}

void copyMesh(vtkSmartPointer<vtkUnstructuredGrid> vtkGrid, getfem::mesh & gmesh)
{
  gmesh.clear();
  auto nnodes = vtkGrid->GetNumberOfPoints();
  std::vector<bgeot::size_type> ind(nnodes);
  for (auto i=0; i<nnodes; ++i)
  {
    double pt[3];
    vtkGrid->GetPoint(i, pt);
    ind[i] = gmesh.add_point(bgeot::base_node(pt[0], pt[1], pt[2]));
  } 
  auto ncells = vtkGrid->GetNumberOfCells();
  auto cm = CellMapping();
  for (auto i=0; i<ncells; ++i)
  {
    vtkIdType npts;
    vtkIdType *pts = nullptr;
    auto cellType = vtkGrid->GetCellType(i);
    if (cellType == 1) continue;
    vtkGrid->GetCellPoints(i, npts, pts);
    cm.setup(cellType);
    cm.mapConnectivity(npts, pts, ind); 
    gmesh.add_convex(cm.getTrans(), ind.begin());
  }
}


} // namespace v2g

