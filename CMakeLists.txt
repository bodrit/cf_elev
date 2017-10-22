cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project (elevator)

#############################
########### PARAMS ##########
#############################
enable_language(CXX)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS                "-std=c++11 -pthread -Wall -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused")
set(CMAKE_CXX_FLAGS_DEBUG          "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE        "-O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_CXX_COMPILER "clang++")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")


#############################
########### FILES ###########
#############################
file(GLOB_RECURSE src_files src/*.cpp src/*.h)
include_directories(
  ${PROJECT_SOURCE_DIR}/src
)


#############################
########### MAIN ############
#############################
add_executable(elevator ${src_files})


#############################
########### GTEST ###########
#############################
add_subdirectory (external/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable( run_tests test/main.cpp test/config_test.cpp src/config.h src/config.cpp)
target_link_libraries(run_tests gtest gtest_main)
add_test( run_tests bin/run_tests )
