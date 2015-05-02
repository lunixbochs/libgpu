include_directories(util)

file(GLOB_RECURSE GPU_SOURCES gpu/*.c util/*.c)
add_library(GPU SHARED ${GPU_SOURCES})

file(GLOB_RECURSE EXAMPLE_SOURCES example/*.c)
add_executable(example ${EXAMPLE_SOURCES})
target_link_libraries(example GPU SDL2)

INSTALL(TARGETS GPU
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
