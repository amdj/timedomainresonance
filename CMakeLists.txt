# CMakeList.txt for linear code
cmake_minimum_required (VERSION 2.8.9)

project(Timedomain1DEuler)

add_definitions(-DTRACERNAME=timedomaineuler -DARMA_USE_BLAS -DARMA_USE_LAPACK)

############################## Not so often changed

# -pipe Use pipes rather than temporary files for communication
#           between the various stages of compilation.  This fails to
#           work on some systems where the assembler is unable to
#           read from a pipe; but the GNU assembler has no troubl.


set (CMAKE_GCC " -Wno-unused-function  -ffunction-sections -fdata-sections -Wno-unused-local-typedefs -Wno-empty-body")

set (CMAKE_GENERAL "${CMAKE_GENERAL} -std=c++11 -pipe -O2 -fPIC -Wall \
 -Wextra -Wno-unused-parameter \
 -Wno-unused-variable -Wno-unused-but-set-variable \
 -Wno-return-local-addr -Wno-cpp  -Wno-address")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_GENERAL} ${CMAKE_GCC}")

# link_directories(${link_directories} /usr/local/lib)
set (tdir /home/anne/wip/tmtubes/src)
include_directories(
  ${tdir}/nonlinear/sys
  ${tdir}/nonlinear/seg
  ${tdir}/nonlinear/geom
  ${tdir}/nonlinear/geom/grid
  ${tdir}/common
  ${tdir}/common/gas
  ${tdir}/common/solid
  src
  )
AUX_SOURCE_DIRECTORY(src src)
link_directories(/home/anne/bin/lib)
add_executable(timedomaineuler timedomain.cpp ${src})

target_link_libraries(timedomaineuler nonlin armadillo boost_program_options)






