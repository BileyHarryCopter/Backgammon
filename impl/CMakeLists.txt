aux_source_directory(src/ SRC_LIST)
add_executable(start ${SRC_LIST})

set (INCLUDE_DIRS include/)
target_include_directories(start
                           PUBLIC ${INCLUDE_DIRS})

find_package(SDL2 REQUIRED)

set (SDL2_LIBRARIES SDL2 SDL2_image SDL2_mixer SDL2_ttf)
target_link_libraries(start
                      ${SDL2_LIBRARIES})
