cmake_minimum_required(VERSION 2.8)
project( blur )
add_executable( blur blur.cpp blur_lib.cpp)

## Compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-O2")        ## Optimize
    set(CMAKE_EXE_LINKER_FLAGS "-s")  ## Strip binary
endif()
