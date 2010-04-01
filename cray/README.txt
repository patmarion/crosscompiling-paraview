---------------------------
Modules:

  Choose your compiler, PGI or GCC.
  Make sure the proper modules are always loaded.

    # switch from PGI to GNU compiler
    module switch PrgEnv-pgi PrgEnv-gnu

    # switch from GNU to PGI compiler
    module switch PrgEnv-gnu PrgEnv-pgi


---------------------------
Platform file:

  copy CRAYXT_COMPUTE_LINUX.cmake to $cmake_install_dir/share/cmake2.x/Modules/Platform/

  The platform file used is basic, but it does some important things-
  It sets TARGET_SUPPORTS_SHARED_LIBS to FALSE and it sets CMAKE_DL_LIBS to "".

---------------------------
Toolchains:

  This folder contains a toolchains folder.  It contains two toolchain files
  one for pgi and one for gnu.  Edit the toolchain files and replace
  /usr/people/pmarion/install/cnl with the directory where you installed the
  cross compiled versions of python and osmesa.  Adjust the other paths to make
  sure they are correct for your system.  Usually two other paths are required,
  one for finding libraries for your compiler environment, and a path for finding
  mpi libraries.  With these paths correctly specified, cmake should be able to
  locate mpi, osmesa, and python automatically.

  The toolchain file sets CMAKE_SYSTEM_NAME to CRAYXT_COMPUTE_LINUX, which
  instructs cmake to use the platform file discussed earlier.

---------------------------
Cross compile paraview dependencies:

  In the python and mesa folders you can find tarballs and instructions
  for cross compiling python and osmesa.

---------------------------
Build the paraview host tools natively:

  Unloaded all xt modules, setup the environment for local builds, not cross compiling.
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
Patching the paraview source:

  Note, this step is not required when using ParaView 3.8 or newer.
  This folder contains a patch which stubs out VTK/Utilities/kwsys/DynamicLoader.cxx
  so that it does not include symbols from libdl.  This may or may not be needed
  depending on if your system supports dynamic libraries.  Since we're doing a static
  build then we might as well use it, so take a look at the patch file:

    fix-for-DynamicLoader.txt

---------------------------
Cross compile paraview

  Create a new build directory and run cmake to configure paraview in
  cross compile mode.  See the file:

    paraview_configure_command.sh

  Note: If you're cross compiling with python support then make sure you set the
  python executable (the cmake variable PYTHON_EXECUTABLE) to a native python
  interpreter, not cross compiled.

  Now run make.

