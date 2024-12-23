add_library(chk_window SHARED)
add_library(chk::window ALIAS chk_window)

target_link_libraries(chk_window
    PUBLIC
        chk::common
    PRIVATE
        glfw
)

target_sources(chk_window
    PRIVATE
        "src/window.c"
        "src/gl.c"
    PUBLIC
    FILE_SET chk_common_headers
    TYPE HEADERS
    BASE_DIRS "include"
    FILES
        "include/chk/window/window.h"
        "include/chk/opengl/gl.h"
        "include/chk/opengl/khrplatform.h"
)
