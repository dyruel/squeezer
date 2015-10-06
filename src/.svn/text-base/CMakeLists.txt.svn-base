project(SQUEEZER)
cmake_minimum_required(VERSION 2.6)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BUILD_TYPE})
set(CMAKE_CXX_FLAGS "-O2 -Wall -DFIXED_PRECISION=double")

file(GLOB_RECURSE SQUEEZER_SOURCE RELATIVE ${SQUEEZER_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE SQUEEZER_INCLUDE RELATIVE ${SQUEEZER_SOURCE_DIR} *.h)

find_package(aGrUM QUIET)
if (aGrUM_FOUND) 
  include(${aGrUM_USE_FILE})
else (aGrUM_FOUND)
  message(FATAL_ERROR "aGrUM library not found")
endif (aGrUM_FOUND)

add_subdirectory(tinyXML)
include_directories(${SQUEEZER_SOURCE_DIR})

add_executable (squeezer ${SQUEEZER_SOURCE} ${SQUEEZER_INCLUDE})
target_link_libraries(squeezer agrum tinyXML)
