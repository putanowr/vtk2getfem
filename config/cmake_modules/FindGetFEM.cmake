# - Try to find GetFEM
# Once done this will define
#
#  GETFEM_FOUND - system has GetFEM
#  GETFEM_INCLUDE_DIRS - the GetFEM include directory
#  GETFEM_INCLUDE_DIR - the GetFEM include directory
#  GETFEM_LIBRARIES - Link these to use GetFEM
#  GETFEM_DEFINITIONS - Compiler switches required for using GetFEM
#
#  Copyright (c) 2018 Roman Putanowicz <putanowr@gmail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#
if (GETFEM_LIBRARIES AND GETFEM_INCLUDE_DIRS)
  # in cache already
  set(GETFEM_FOUND TRUE)
else (GETFEM_LIBRARIES AND GETFEM_INCLUDE_DIRS)
  find_path(GETFEM_INCLUDE_DIR NAMES getfem/getfem_mesh.h
    PATHS  ENV CPLUS_INCLUDE_PATH
           "${BASE_DIR}/include" NO_DEFAULT_PATH
  )
  find_path(GETFEM_INCLUDE_DIR NAMES getfem/getfem_mesh.h
  )

  find_library(GETFEM_LIBRARY NAMES getfem PATHS ENV LD_LIBRARY_PATH
              "${BASE_DIR_LIB}"
    NO_DEFAULT_PATH
  )
  find_library(GETFEM_LIBRARY NAMES getfem 
  )
  set(GETFEM_INCLUDE_DIRS
    ${GETFEM_INCLUDE_DIR} CACHE PATH "Path to GetFEM++ headers"
  )

  set(GETFEM_INCLUDE_DIR
    ${GETFEM_INCLUDE_DIR} CACHE PATH "Path to GetFEM++ headers"
  )
  set(GETFEM_LIBRARIES
      ${GETFEM_LIBRARY} CACHE STRING "Directories to be linked to use GetFEM++"
  )

  include(FindPackageHandleStandardArgs)
  # handle the QUIETLY and REQUIRED arguments and set GETFEM_FOUND to TRUE
  # if all listed variables are TRUE
  find_package_handle_standard_args(GetFEM  DEFAULT_MSG
                                  GETFEM_LIBRARY GETFEM_INCLUDE_DIR)
  if (GETFEM_FOUND)
    message(STATUS "GetFEM header files: ${GETFEM_INCLUDE_DIR}")
    message(STATUS "GetFEM library: ${GETFEM_LIBRARY}")
  endif (GETFEM_FOUND)
  mark_as_advanced(GETFEM_INCLUDE_DIRS GETFEM_LIBRARIES)
endif (GETFEM_LIBRARIES AND GETFEM_INCLUDE_DIRS)

