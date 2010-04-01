# Set the install directory
# Edit MesaLib-7.0.4/configs/default to set the INSTALL_DIR to something like:

INSTALL_DIR = $(HOME)/install/xlc-bgl

# Mesa come with a make configuration for bluegene xlc.
# The configuration is located in configs/bluegene-xlc-osmesa.
# You can edit this configuration file to make sure it has the right
# compiler paths for xlC on your system.

# Now just run make with the bluegene xlc configuration:

make bluegene-xlc-osmesa
make install

