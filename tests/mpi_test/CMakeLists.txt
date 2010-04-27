project(test)
cmake_minimum_required(VERSION 2.6)

find_package(MPI)

include_directories(${MPI_INCLUDE_PATH})
add_executable(hello hello.cxx)
target_link_libraries(hello ${MPI_LIBRARY} ${MPI_EXTRA_LIBRARY})
