# How to cross compile python 2.5.2 with cmake:

# Extract python
tar -zxf Python-2.5.2.tgz

# Patch python to create cmake files
patch -p1 -d Python-2.5.2 < add_cmake_files_to_python2-5-2.patch

# Cross compile python
mkdir build-python2-5-2
cd build-python2-5-2
cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/toolchain.cmake -DCMAKE_INSTALL_PREFIX=/path/to/install ../Python-2.5.2
make
make install

# Note, you may want to turn off certain options, such as THREADS or IPV6.
# The posix module is required.
# You may want to turn on BUILD_UNTESTED_MODULES to get things like math,
# but you may have to disable certain modules if they have build errors.
