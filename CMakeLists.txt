cmake_minimum_required(VERSION 3.8)

project(FOOBAR)

# set module path to include cmake directory
set(CMAKE_MODULE_PATH
  ${CMAKE_SOURCE_DIR}/cmake
  ${CMAKE_MODULE_PATH})

# enable cuda
enable_language(CUDA)

set(FOOBAR_LANGUAGE CUDA)

# include directories
# to indicate system header location
#include_directories(SYSTEM dir)
#include_directories(${CMAKE_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# find foobar source files
file(GLOB_RECURSE foobar_source foobar/*.cc)
set_source_files_properties(${foobar_source} PROPERTIES LANGUAGE ${FOOBAR_LANGUAGE})

# compile for cpp
add_library(foobar STATIC ${foobar_source})

# dependencies

# compiler features
target_compile_features(foobar PUBLIC cxx_std_11)

# compiler options
target_compile_options(foobar PUBLIC -arch compute_30)

# compiler definitions
# target_compile_definitions()

# foobar executable function
function(foobar_executable target source_files)
  add_executable(${target} ${source_files})
  set_source_files_properties(${source_files} PROPERTIES LANGUAGE ${FOOBAR_LANGUAGE})
  target_link_libraries(${target} foobar)
endfunction()

# subdirectories
add_subdirectory(exec)

#message("CMAKE_CUDA_LINK_EXECUTABLE: " ${CMAKE_CUDA_LINK_EXECUTABLE})
#message("CMAKE_CUDA_HOST_LINK_LAUNCHER: " ${CMAKE_CUDA_HOST_LINK_LAUNCHER})
#message("CMAKE_CUDA_DEVICE_LINK_EXECUTABLE: " ${CMAKE_CUDA_DEVICE_LINK_EXECUTABLE})
#message("CMAKE_CUDA_LINK_FLAGS: " ${CMAKE_CUDA_LINK_FLAGS})
#message("FLAGS: " "${FLAGS}")
