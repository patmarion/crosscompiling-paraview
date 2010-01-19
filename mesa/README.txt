# Copy config file (cnl-osmesa-gnu or cnl-osmesa-pgi) to MesaLib-7.0.4/configs/
# Edit MesaLib-7.0.4/Makefile to add config filename to list of available config files

# Set the install directory
# Edit MesaLib-7.0.4/configs/default to set the INSTALL_DIR to something like:

INSTALL_DIR = $(HOME)/install/cnl-pgi

# Now run make with the chosen configuration:

make cnl-osmesa-pgi
make install
