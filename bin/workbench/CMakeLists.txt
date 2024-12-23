add_executable(chk_workbench)

target_compile_definitions(chk_workbench
    PRIVATE
        "-DCHK_LOG_PATH_BASE=\"${CMAKE_CURRENT_SOURCE_DIR}/../\""
)

target_link_libraries(chk_workbench
    PUBLIC
        chk::common
        chk::window
)

target_sources(chk_workbench
    PRIVATE
        "src/main.c"
    PUBLIC
    FILE_SET chk_workbench_headers
    TYPE HEADERS
    BASE_DIRS "include"
    FILES
        "include/chk/workbench/workbench.h"
)
