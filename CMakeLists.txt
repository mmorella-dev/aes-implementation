# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.24.2)
project (AES)
set (CMAKE_CXX_STANDARD 20)

add_subdirectory(src)