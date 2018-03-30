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

void exportMesh(const Manager &myManager, const getfem::mesh &);

} // namespace v2g
