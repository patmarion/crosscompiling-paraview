cmake_minimum_required(VERSION 2.6)
project(osmesa-test)

# Find OSMesa include dir and libs
set(mesa_dir Mesa-7.0.2)

find_path(MESA_INCLUDE_DIR GL/osmesa.h ${mesa_dir}/include NO_DEFAULT_PATH)
find_library(MESA_OSMESA_LIBRARY OSMesa ${mesa_dir}/lib NO_DEFAULT_PATH)
find_library(MESA_GLU_LIBRARY GLU ${mesa_dir}/lib NO_DEFAULT_PATH)

include_directories(${MESA_INCLUDE_DIR})
add_executable(osdemo osdemo.c)
target_link_libraries(osdemo ${MESA_GLU_LIBRARY} ${MESA_OSMESA_LIBRARY})
