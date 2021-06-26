# spatula/docs/CMakeLists.txt

find_package(Doxygen REQUIRED)

# Doxyfile configuration
set(DOXYGEN_INPUT_DIR ${spatula_SOURCE_DIR}/include/spatula)
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR} PARENT_SCOPE)

set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

# the path for the index html file output
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)
add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                   DEPENDS ${spatula_HEADERS}
                   COMMAND Doxygen::doxygen ${DOXYFILE_OUT}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   MAIN_DEPENDENCY Doxyfile
                   COMMENT "Generating docs")

add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})
