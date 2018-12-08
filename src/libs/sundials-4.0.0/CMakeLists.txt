# ---------------------------------------------------------------
# Programmer: Radu Serban, David J. Gardner, Cody J. Balos,
#             and Slaven Peles @ LLNL
# ---------------------------------------------------------------
# LLNS Copyright Start
# Copyright (c) 2014, Lawrence Livermore National Security
# This work was performed under the auspices of the U.S. Department
# of Energy by Lawrence Livermore National Laboratory in part under
# Contract W-7405-Eng-48 and in part under Contract DE-AC52-07NA27344.
# Produced at the Lawrence Livermore National Laboratory.
# All rights reserved.
# For details, see the LICENSE file.
# LLNS Copyright End
# ---------------------------------------------------------------
# Top level CMakeLists.txt for SUNDIALS (for cmake build system)
# ---------------------------------------------------------------

# Project SUNDIALS (initially only C supported)
# sets PROJECT_SOURCE_DIR and PROJECT_BINARY_DIR variables
PROJECT(sundials C)

OPTION(BUILD_STATIC_LIBS "Build static libraries" ON)
OPTION(BUILD_SHARED_LIBS "Build shared libraries" OFF)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)


# ---------------------------------------------------------------
# Programmer: David J. Gardner @ LLNL
#             Radu Serban @ LLNL
# ---------------------------------------------------------------
# LLNS Copyright Start
# Copyright (c) 2014, Lawrence Livermore National Security
# This work was performed under the auspices of the U.S. Department 
# of Energy by Lawrence Livermore National Laboratory in part under 
# Contract W-7405-Eng-48 and in part under Contract DE-AC52-07NA27344.
# Produced at the Lawrence Livermore National Laboratory.
# All rights reserved.
# For details, see the LICENSE file.
# LLNS Copyright End
# ---------------------------------------------------------------
# CMake macros used throughout the SUNDIALS build system
# ---------------------------------------------------------------

MACRO(ADD_PREFIX prefix rootlist)
  SET(outlist )
  FOREACH(root ${${rootlist}})
    LIST(APPEND outlist ${prefix}${root})
  ENDFOREACH(root)
  SET(${rootlist} ${outlist})
ENDMACRO(ADD_PREFIX)


# ---------------------------------------------------------------
# Programmer:  David Gardner and Slaven Peles @ LLNL
# ---------------------------------------------------------------
# LLNS Copyright Start
# Copyright (c) 2014, Lawrence Livermore National Security
# This work was performed under the auspices of the U.S. Department
# of Energy by Lawrence Livermore National Laboratory in part under
# Contract W-7405-Eng-48 and in part under Contract DE-AC52-07NA27344.
# Produced at the Lawrence Livermore National Laboratory.
# All rights reserved.
# For details, see the LICENSE file.
# LLNS Copyright End
# ---------------------------------------------------------------
# src level CMakeLists.txt for SUNDIALS (for cmake build system)
# ---------------------------------------------------------------

# Always add SUNDIALS provided serial modules
ADD_SUBDIRECTORY(src/sundials)
ADD_SUBDIRECTORY(src/nvec_ser)
ADD_SUBDIRECTORY(src/sunmat_dense)
ADD_SUBDIRECTORY(src/sunmat_band)
ADD_SUBDIRECTORY(src/sunmat_sparse)
ADD_SUBDIRECTORY(src/sunlinsol_band)
ADD_SUBDIRECTORY(src/sunlinsol_dense)

# Always add SUNDIALS provided iterative linear solver modules
ADD_SUBDIRECTORY(src/sunlinsol_spgmr)
ADD_SUBDIRECTORY(src/sunlinsol_spfgmr)
ADD_SUBDIRECTORY(src/sunlinsol_spbcgs)
ADD_SUBDIRECTORY(src/sunlinsol_sptfqmr)
ADD_SUBDIRECTORY(src/sunlinsol_pcg)

# Add nonlinerar solver modules
ADD_SUBDIRECTORY(src/sunnonlinsol)

# CVODE library
ADD_SUBDIRECTORY(src/cvode)
