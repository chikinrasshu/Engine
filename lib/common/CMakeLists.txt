add_library(chk_common SHARED)
add_library(chk::common ALIAS chk_common)

target_compile_definitions(chk_common
    PRIVATE
        "-DCHK_LOG_PATH_BASE=\"${CMAKE_CURRENT_SOURCE_DIR}/../\""
)

target_link_libraries(chk_common
    PRIVATE
        cwalk
)

target_sources(chk_common
    PRIVATE
        "src/arena.c"
        "src/fmt.c"
        "src/log.c"
    PUBLIC
    FILE_SET chk_common_headers
    TYPE HEADERS
    BASE_DIRS "include"
    FILES
        "include/chk/common/arena.h"
        "include/chk/common/common.h"
        "include/chk/common/fmt.h"
        "include/chk/common/input.h"
        "include/chk/common/log.h"
        "include/chk/common/types.h"
)
