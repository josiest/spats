find_package(Catch2 REQUIRED)

file(GLOB geometry_test_sources *.cpp)
add_executable(geometery_test geometry/${geometry_test_sources})

list(APPEND all_tests geometry_test)
foreach(test ${all_tests})
    targt_link_libraries(${test} Catch2::Catch2 Catch2::Catch2WithMain)
endforeach()


# file(GLOB example_sources *.cpp)
# foreach(example_source ${example_sources})
# 
#     # get the file name without its extension
#     get_filename_component(example_name ${example_source} NAME_WE)
# 
#     # add the executables
#     add_executable(${example_name} ${example_source})
# 
# endforeach(example_source ${EXAMPES})