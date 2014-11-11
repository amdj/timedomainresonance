# CMakeList.txt for linear code
cmake_minimum_required (VERSION 2.8.9)

project(Timedomain1DEuler)

add_definitions(-DTRACERNAME=timedomaineuler -DARMA_USE_BLAS -DARMA_USE_LAPACK)

############################## Not so often changed

# -pipe Use pipes rather than temporary files for communication
#           between the various stages of compilation.  This fails to
#           work on some systems where the assembler is unable to
#           read from a pipe; but the GNU assembler has no troubl.


# ${tubedrag}
set (CMAKE_GCC " -Wno-unused-function  -ffunction-sections -fdata-sections -Wno-unused-local-typedefs -Wno-empty-body")



set (CMAKE_GENERAL "${CMAKE_GENERAL} -std=c++11 -pipe -fPIC -Wall \
 -Wextra -Wno-unused-parameter \
 -Wno-unused-variable -Wno-unused-but-set-variable \
 -Wno-return-local-addr -Wno-cpp  -Wno-address")


set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_GENERAL} ${CMAKE_GCC}")

link_directories(${link_directories} /usr/local/lib)
include_directories(
  ../tmtubes/src
  ../tmtubes/src/sys
  ../tmtubes/src/seg
  ../tmtubes/src/common
  ../tmtubes/src/common/gas
  ../tmtubes/src/common/bessel
  ../tmtubes/src/common/fsolve  
  ../tmtubes/src/common/solid
  ../tmtubes/src/common/rottfuncs
  )
AUX_SOURCE_DIRECTORY(src src)
link_directories(tmtubes/src/nonlinear tmtubes/src/common)
# set(src ${src} src/seg/geom.cpp src/sys/globalconf.cpp)
add_executable(timedomaineuler timedomain.cpp ${src})

target_link_libraries(timedomaineuler nonlin math_common blas lapack boost_iostreams boost_serialization)






