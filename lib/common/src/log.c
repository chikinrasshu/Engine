#include <chk/common/log.h>

#include <cwalk.h>
#include <stdio.h>
#include <stdlib.h>

void chk_impl_log_v(chk_log_level_t lvl, const char *msg, const char *file_base, const char *file, int line,
                    const char *func, va_list args) {
    static char fmt_msg[1024];

    va_list args_copy;
    va_copy(args_copy, args);
    vsnprintf(fmt_msg, sizeof(fmt_msg), msg, args_copy);
    va_end(args_copy);

    chk_impl_log(lvl, fmt_msg, file_base, file, line, func);
}

void chk_impl_log_f(chk_log_level_t lvl, const char *msg, const char *file_base, const char *file, int line,
                    const char *func, ...) {
    va_list args;
    va_start(args, func);
    chk_impl_log_v(lvl, msg, file_base, file, line, func, args);
    va_end(args);
}

void chk_impl_log(chk_log_level_t lvl, const char *msg, const char *file_base, const char *file, int line,
                  const char *func) {
    const char *lvl_str;
    switch (lvl) {
        case CHK_LOG_LEVEL_DEBUG: lvl_str = "DEBUG"; break;
        case CHK_LOG_LEVEL_INFO: lvl_str = "INFO"; break;
        case CHK_LOG_LEVEL_WARN: lvl_str = "WARN"; break;
        case CHK_LOG_LEVEL_ERROR: lvl_str = "ERROR"; break;
        case CHK_LOG_LEVEL_FATAL: lvl_str = "FATAL"; break;
        default: lvl_str = "UNKNOWN"; break;
    }

    static char rel_file[1024];
    const char *rel_path = file;

    if (cwk_path_get_relative(file_base, file, rel_file, sizeof(rel_file))) { rel_path = rel_file; }

    fprintf(stderr, "%s | %s:%d %s | %s\n", lvl_str, rel_path, line, func, msg);

    if (lvl == CHK_LOG_LEVEL_FATAL) { abort(); }
}
