---------------------------
Compilers:

  These are instructions are for the xlC compiler on Bluegene/L

---------------------------
Toolchains:

  This folder contains a toolchains folder.  It contains a toolchain file
  one the xlC compiler.  Edit the toolchain files and replace
  /home/pat/install/xlc-bgl with the directory where you installed the
  cross compiled versions of python and osmesa.  Adjust the other paths to make
  sure they are correct for your system.  Usually two other paths are required,
  one for finding libraries for your compiler environment, and a path for finding
  mpi libraries.  With these paths correctly specified, cmake should be able to
  locate mpi, osmesa, and python automatically.

  The toolchain file sets CMAKE_SYSTEM_NAME to BlueGeneL, which
  instructs cmake to use the bluegene/l platform file located in
  $cmake_install_dir/share/cmake-2.8/Modules/Platform/BlueGeneL.cmake.

---------------------------
Cross compile paraview dependencies:

  In the python and mesa folders you can find tarballs and instructions
  for cross compiling python and osmesa.

---------------------------
Build the paraview host tools natively:

  Setup the environment for local builds, not cross compiling.
  Try typing 'which cc' to see that it is the one in /usr/bin and not a cross compile wrapper.
  Create a paraview_host_tools_build directory, then configure paraview with cmake using
  default options.  Then build just the needed tools (should be relatively quick):

    make pvHostTools

  Note: If you plan to cross compile paraview with python support then you'll need
  to enable python for this host tools build too.

  The host tools are native helper executables that will be used when cross
  compiling paraview.  For example, a helper exe must be used to generate python wrapped
  cxx source files.

---------------------------
Cross compile paraview

  Create a new build directory and run cmake to configure paraview in
  cross compile mode.  See the file:

    paraview_configure_command.sh

  Note: If you're cross compiling with python support then make sure you set the
  python executable (the cmake variable PYTHON_EXECUTABLE) to a native python
  interpreter, not cross compiled.

  Now run make.

