
file(GLOB EXAMPLES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
foreach(example_source ${EXAMPLES})
    get_filename_component(example_name ${example_source} NAME_WE)
    add_executable(${example_name} ${example_source})
    target_include_directories(${example_name} PUBLIC ${spatula_INCLUDE_DIRS})
endforeach(example_source ${EXAMPES})
