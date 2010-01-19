# How to build python 2.5.2 with cmake:

# Extract python
tar -zxf Python-2.5.2.tgz

# Patch python to create cmake files
patch -p1 -d Python-2.5.2 < add_cmake_files_to_python2-5-2.patch

# Build python
mkdir build-python2-5-2
cd build-python2-5-2
ccmake ../Python-2.5.2
make


