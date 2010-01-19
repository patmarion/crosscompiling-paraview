project(test-python)


cmake_minimum_required(VERSION 2.6)

find_package(PythonLibs)

include_directories(${PYTHON_INCLUDE_PATH})
add_executable(main main.cxx)
target_link_libraries(main ${PYTHON_LIBRARIES})


