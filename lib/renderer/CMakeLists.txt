add_library(chk_renderer SHARED)
add_library(chk::renderer ALIAS chk_renderer)

target_compile_definitions(chk_renderer
    PRIVATE
        "-DCHK_LOG_PATH_BASE=\"${CMAKE_CURRENT_SOURCE_DIR}/../\""
)

target_link_libraries(chk_renderer
    PUBLIC
        chk::common
    PRIVATE
        chk::opengl
)

target_sources(chk_renderer
    PRIVATE
        "src/color.c"
        "src/renderer.c"
    PUBLIC
    FILE_SET chk_renderer_headers
    TYPE HEADERS
    BASE_DIRS "include"
    FILES
        "include/chk/renderer/color.h"
        "include/chk/renderer/renderer.h"
)
