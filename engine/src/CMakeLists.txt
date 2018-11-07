aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_DIR)

#log
add_definitions(-D YM_DEBUG)

include_directories(${ENGINE_DIR}/include)
link_directories(${ENGINE_DIR}/lib)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_DIR)

set(LIBRARY_OUTPUT_PATH ${ENGINE_DIR}/lib)

add_library(engine STATIC ${SRC_DIR})

