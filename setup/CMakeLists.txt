aux_source_directory(src/ SRC_LIST)
add_executable(start ${SRC_LIST})

set (INCLUDE_DIRS include/)
target_include_directories(start
                           PUBLIC ${INCLUDE_DIRS})

find_package(SDL2 REQUIRED)
target_link_libraries(start
                      ${SDL2_LIBRARIES})
