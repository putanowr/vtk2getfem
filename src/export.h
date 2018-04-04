// Copyright (c) 2018 Roman Putanowicz
//! @brief Implement export of the mesh.

#pragma once

namespace getfem 
{
 class mesh;
}

namespace v2g 
{
class Manager;
class Model;

void exportData(const Manager &myManager, const getfem::mesh &mesh);
void exportData(const Manager &myManager, const Model &model);

} // namespace v2g
