# spatula/CMakeLists.txt

cmake_minimum_required(VERSION 3.12)

project(spatula VERSION 0.1.0)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# specify file interface
set(spatula_SRCEXT hpp)
set(spatula_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# add test sub-directory if specified
option(run_tests "Run tests" off)
if (run_tests)
    add_compile_definitions(DEBUG)
    add_subdirectory(test)
endif()

# --- create library ---

add_library(spatula INTERFACE)
target_include_directories(spatula INTERFACE
    $<BUILD_INTERFACE:${spatula_SOURCE_DIR}/spatula>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# -- export library --

# install the target and create the export set
install(TARGETS spatula
        EXPORT spatulaTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

# --- create package for library ---

# include helper functions for creating config files
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/spatulaConfigVersion.cmake
    VERSION ${spatula_VERSION}
    COMPATIBILITY AnyNewerVersion)

# generate the package configuration file
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/spatulaConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/spatula)

# allow exporting from build tree
export(EXPORT spatulaTargets
       FILE ${CMAKE_CURRENT_BINARY_DIR}/spatulaTargets.cmake
       NAMESPACE spatula::)

# install the generated files
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/spatulaConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/spatulaConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/spatula)

# install the include files
install(DIRECTORY ${spatula_SOURCE_DIR}/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.${spatula_SRCEXT}")

export(PACKAGE spatula)
