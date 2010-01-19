---------------------------
Modules:

  Try building with gcc if you can, else use pgi compiler.
  Make sure the proper modules are always loaded.

    ## switch from PGI to GNU compiler
    module switch PrgEnv-pgi PrgEnv-gnu

    ## switch from GNU to PGI compiler
    module switch PrgEnv-gnu PrgEnv-pgi


--------------------
Platform file:

  copy CRAYXT_COMPUTE_LINUX.cmake to $cmake_install_dir/share/cmake2.x/Modules/Platform/

---------------------
Build the paraview host tools natively:

  Unloaded all xt modules, setup the environment for local builds, not cross compiling.
  Create a paraview_host_tools_build directory, then run cmake on the paraview
  source dir, then build just the needed tools (should be relatively quick):

    make pvHostTools

  Note: If you plan to cross compile paraview with python support then you'll need
  to enable python for this host tools build too.

---------------------------
Toolchains:

  This folder contains a toolchains folder.  It contains two toolchain files
  which are both exactly the same (one just has pgi in the filename).  Edit
  the toolchain files and replace /usr/people/marionp/install with the directory
  where you installed crosscompiled versions of python and osmesa.

----------------------------
TryRunResults:

  This folder contains a TryRunResults file for gcc.  The same file should
  work fine for pgi.

----------------------------
Patching the source:

  This folder contains a patch which stubs out kwsys/DynamicLoader.cxx so it does
  not include symbols from libdl.  This may or may not be needed depending on if
  your system supports dynamic libraries.  If you intend to do a static build with
  no shared libs then look at the file: fix-for-DynamicLoader.txt


----------------------------
Cross compile paraview


  Run cmake to configure paraview in crosscompile mode (replace $path_name with
  correct paths):

    ccmake -DCMAKE_TOOLCHAIN_FILE=$toolchain_dir/cray-cnl-gnu-toolchain.cmake -DParaView3CompileTools_DIR=$paraview_host_tools_build -DPARAVIEW_BUILD_QT_GUI=0 -C TryRunResults-ParaView3-CNL-gcc.cmake $paraview_source_dir

  make

  Note: If you're cross compiling with python support then make sure you set the
  python executable (the one assigned to the cmake variable PYTHON_EXECUTABLE)
  to a natively built python (not cross compiled).

-------------------------
Further reading

  In the command line specified in the above section 'Cross compile paraview' you instruct
  cmake to include a toolchain file.  The toolchain file sets CMAKE_SYSTEM_NAME to be
  CRAYXT_COMPUTE_LINUX.  This causes cmake to use the CRAYXT_COMPUTE_LINUX.cmake platform
  file.  This platform file tells cmake that the platform does not support shared libs:

    SET_PROPERTY(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS FALSE)








