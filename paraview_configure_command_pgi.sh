#!/bin/bash

cmake \
-DCMAKE_TOOLCHAIN_FILE=~/toolchains/cray-cnl-pgi-toolchain.cmake \
-DParaView3CompileTools_DIR=~/source/paraview/build-host-tools/ \
-DPARAVIEW_USE_MPI=1 \
-DPARAVIEW_ENABLE_PYTHON=1 \
-DPARAVIEW_BUILD_QT_GUI=0 \
-DENABLE_MPI4PY=0 \
-DBUILD_TESTING=0 \
-DOPENGL_gl_LIBRARY="" \
-DCMAKE_CXX_FLAGS="-fastsse -O3" \
-C ~/source/paraview/ParaView/CMake/TryRunResults-ParaView3-cnl-pgi.cmake \
~/source/paraview/ParaView

# Flags for coprocessing
#-DPARAVIEW_ENABLE_COPROCESSING=1 \
#-DBUILD_COPROCESSING_ADAPTORS=1 \
#-DBUILD_FORTRAN_COPROCESSING_ADAPTORS=1 \
#-DBUILD_PYTHON_COPROCESSING_ADAPTOR=1 \
#-DBUILD_PHASTA_ADAPTOR=1 \

# Optionally turn off some libraries
#-DVTK_USE_INFOVIS=0 \
#-DVTK_USE_METAIO=0 \

