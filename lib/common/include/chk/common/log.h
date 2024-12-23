#pragma once

#include <chk/common/types.h>

#ifndef CHK_LOG_PATH_BASE
#    define CHK_LOG_PATH_BASE "/"
#endif

typedef enum chk_log_level {
    CHK_LOG_LEVEL_DEBUG = 0,
    CHK_LOG_LEVEL_INFO,
    CHK_LOG_LEVEL_WARN,
    CHK_LOG_LEVEL_ERROR,
    CHK_LOG_LEVEL_FATAL,
} chk_log_level_t;

void chk_impl_log_v(chk_log_level_t lvl, const char *msg, const char *file_base, const char *file, int line,
                    const char *func, va_list args);
void chk_impl_log_f(chk_log_level_t lvl, const char *msg, const char *file_base, const char *file, int line,
                    const char *func, ...);
void chk_impl_log(chk_log_level_t lvl, const char *msg, const char *file_base, const char *file, int line,
                  const char *func);

#define chk_log(lvl, msg, ...)                                                                                         \
    chk_impl_log##__VA_OPT__(_f)(lvl, msg, CHK_LOG_PATH_BASE, __FILE__, __LINE__, __func__ __VA_OPT__(, ) __VA_ARGS__)

#define chk_log_debug(msg, ...) chk_log(CHK_LOG_LEVEL_DEBUG, msg, __VA_ARGS__)
#define chk_log_info(msg, ...)  chk_log(CHK_LOG_LEVEL_INFO, msg, __VA_ARGS__)
#define chk_log_warn(msg, ...)  chk_log(CHK_LOG_LEVEL_WARN, msg, __VA_ARGS__)
#define chk_log_error(msg, ...) chk_log(CHK_LOG_LEVEL_ERROR, msg, __VA_ARGS__)
#define chk_log_fatal(msg, ...) chk_log(CHK_LOG_LEVEL_FATAL, msg, __VA_ARGS__)
