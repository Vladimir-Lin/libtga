cmake_minimum_required(VERSION 3.0)
PROJECT(libbmp)
INCLUDE (CheckIncludeFile)

include_directories(include)

SET(HEADERS include/libbmp.hpp)
SET(CORES src/bmp.cpp)

if(BUILD_SHARED_LIBS)
  ADD_LIBRARY(libbmp SHARED ${CORES} ${HEADERS})
  add_definitions("-DBUILD_SHARED_LIBS=1")
  add_definitions("-DEXPORT_LIBBMP=1")
  install(TARGETS libbmp
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
  install(FILES include/libbmp.hpp DESTINATION include)
else(BUILD_SHARED_LIBS)
  ADD_LIBRARY(libbmp STATIC ${CORES} ${HEADERS})
  install(TARGETS libbmp DESTINATION lib)
  install(FILES include/libbmp.hpp DESTINATION include)
endif(BUILD_SHARED_LIBS)
