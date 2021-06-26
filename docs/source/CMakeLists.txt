# spatula/docs/source/CMakeLists.txt

find_package(Sphinx REQUIRED)

# sphinx directories
set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR})

message("doxygen output dir: ${DOXYGEN_OUTPUT_DIR}/xml")

# define the sphinx build command
add_custom_target(
    Sphinx ALL
    COMMAND ${SPHINX_EXECUTABLE} -b html
    # Tell breather where to find Doxygen output
    -Dbreathe_projects.spatula=${DOXYGEN_OUTPUT_DIR}/xml
    ${SPHINX_SOURCE} ${SPHINX_BUILD}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating documentation with Sphinx")
