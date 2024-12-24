add_executable(chk_workbench)

target_compile_definitions(chk_workbench
    PRIVATE
        "-DCHK_LOG_PATH_BASE=\"${CMAKE_CURRENT_SOURCE_DIR}/../\""
)

target_link_libraries(chk_workbench
    PUBLIC
        chk::common
        chk::renderer
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

add_custom_command(TARGET chk_workbench POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:chk_workbench> $<TARGET_FILE_DIR:chk_workbench>
    COMMAND_EXPAND_LISTS
)