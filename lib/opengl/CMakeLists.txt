add_library(chk_opengl SHARED)
add_library(chk::opengl ALIAS chk_opengl)

target_compile_definitions(chk_opengl
    PRIVATE
        "-DCHK_LOG_PATH_BASE=\"${CMAKE_CURRENT_SOURCE_DIR}/../\""
)

target_link_libraries(chk_opengl
    PUBLIC
        chk::common
)

target_sources(chk_opengl
    PRIVATE
        "src/opengl.c"
        "src/loader.c"
    PUBLIC
    FILE_SET chk_opengl_headers
    TYPE HEADERS
    BASE_DIRS "include"
    FILES
        "include/chk/opengl/opengl.h"
        "include/chk/opengl/loader.h"
        "include/chk/opengl/khrplatform.h"
)

