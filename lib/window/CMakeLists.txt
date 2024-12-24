add_library(chk_window SHARED)
add_library(chk::window ALIAS chk_window)

target_compile_definitions(chk_window
    PRIVATE
        "-DCHK_LOG_PATH_BASE=\"${CMAKE_CURRENT_SOURCE_DIR}/../\""
)

target_link_libraries(chk_window
    PUBLIC
        chk::common
        chk::opengl
    PRIVATE
        glfw
)

target_sources(chk_window
    PRIVATE
        "src/window.c"
    PUBLIC
    FILE_SET chk_window_headers
    TYPE HEADERS
    BASE_DIRS "include"
    FILES
        "include/chk/window/window.h"
)

if(WIN32)
    target_link_libraries(chk_window
        PRIVATE
            Comctl32.lib
            dwmapi
    )

    target_sources(chk_window
        PRIVATE
            "src/win32/window.c"
        PUBLIC
        FILE_SET chk_window_headers
        TYPE HEADERS
        BASE_DIRS "include"
        FILES
            "include/chk/window/win32/window.h"
    )
endif()
