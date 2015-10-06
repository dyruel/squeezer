
cmake_minimum_required(VERSION 2.6)
find_package(PythonInterp)

find_package(aGrUM QUIET)
if (aGrUM_FOUND) 
  include(${aGrUM_USE_FILE})
else (aGrUM_FOUND)
  message(FATAL_ERROR "aGrUM library not found")
endif (aGrUM_FOUND)

set(CXXTESTGEN ${CMAKE_SOURCE_DIR}/cxxtest/cxxtestgen.py)

MACRO(ADD_CXXTEST NAME)
  IF(PYTHONINTERP_FOUND)
    ADD_CUSTOM_COMMAND(
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.cpp
      COMMAND
        ${PYTHON_EXECUTABLE} ${CXXTESTGEN}
        --error-printer
        -o ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.cpp ${ARGN}
      DEPENDS ${ARGN}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
  ELSE(PYTHONINTERP_FOUND)
  	message(FATAL_ERROR "python not found")
  ENDIF(PYTHONINTERP_FOUND)

  ADD_EXECUTABLE(${NAME} ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.cpp ${ARGN})

  ADD_TEST(${NAME} ${NAME})
ENDMACRO(ADD_CXXTEST)

#########################################################################################

include_directories(cxxtest)
include_directories(${CMAKE_SOURCE_DIR}/../src)

file(GLOB SQUEEZER_TESTS *Suite.h)

add_cxxtest(test ${SQUEEZER_TESTS})

target_link_libraries(test agrum)
