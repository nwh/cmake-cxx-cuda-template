cmake_minimum_required(VERSION 3.8)

project(FOOBAR)

enable_testing()

# set module path to include cmake directory
set(CMAKE_MODULE_PATH
  ${CMAKE_SOURCE_DIR}/cmake
  ${CMAKE_MODULE_PATH})

# language switch
set(FOOBAR_LANGUAGE "CXX" CACHE STRING "Selected language {CXX,CUDA}")

# check for valid FOOBAR_LANGUAGE
if(${FOOBAR_LANGUAGE} STREQUAL "CXX")
elseif(${FOOBAR_LANGUAGE} STREQUAL "CUDA")
  # enable CUDA
  enable_language(CUDA)
  # CMAKE_CUDA_FLAGS is where gpu architecture should be specified
  set(CMAKE_CUDA_FLAGS "-arch compute_30 ${CMAKE_CUDA_FLAGS}")
else()
  message(FATAL_ERROR "${FOOBAR_LANGUAGE} is not a supported language.")
endif()

# googletest
include(DownloadProject)
download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             master
                 UPDATE_DISCONNECTED 1
)
add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

# include directories
# to indicate system header location
#include_directories(SYSTEM dir)
#include_directories(${CMAKE_BINARY_DIR})
#include_directories(${CMAKE_SOURCE_DIR})

# find foobar source files
file(GLOB_RECURSE foobar_source foobar/*.cc)
set_source_files_properties(${foobar_source} PROPERTIES LANGUAGE ${FOOBAR_LANGUAGE})

# compile for cpp
add_library(foobar STATIC ${foobar_source})
add_dependencies(foobar gtest)
target_compile_features(foobar PUBLIC cxx_std_11)
target_include_directories(foobar PUBLIC ${CMAKE_SOURCE_DIR})
# target_compile_options()
# target_compile_definitions()

# foobar executable function
function(foobar_executable target source_files)
  add_executable(${target} ${source_files})
  set_source_files_properties(${source_files} PROPERTIES LANGUAGE ${FOOBAR_LANGUAGE})
  target_link_libraries(${target} foobar)
endfunction()

# foobar test function
function(foobar_test target source_files)
  add_executable(${target} ${source_files})
  target_link_libraries(${target} foobar gtest_main)
  add_test(NAME ${target} COMMAND ${target})
endfunction()

# subdirectories
add_subdirectory(exec)
add_subdirectory(test)

#message("CMAKE_CUDA_LINK_EXECUTABLE: " ${CMAKE_CUDA_LINK_EXECUTABLE})
#message("CMAKE_CUDA_HOST_LINK_LAUNCHER: " ${CMAKE_CUDA_HOST_LINK_LAUNCHER})
#message("CMAKE_CUDA_DEVICE_LINK_EXECUTABLE: " ${CMAKE_CUDA_DEVICE_LINK_EXECUTABLE})
#message("CMAKE_CUDA_LINK_FLAGS: " ${CMAKE_CUDA_LINK_FLAGS})
#message("FLAGS: " "${FLAGS}")
#message("CMAKE_CUDA_FLAGS: " "${CMAKE_CUDA_FLAGS}")
