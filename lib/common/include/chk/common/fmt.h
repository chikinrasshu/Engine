#pragma once

#include <chk/common/types.h>

s32 chk_impl_fmt_v(char *buf, size_t buf_size, const char *msg, va_list args);
s32 chk_impl_fmt_f(char *buf, size_t buf_size, const char *msg, ...);
s32 chk_impl_fmt(char *buf, size_t buf_size, const char *msg);

#define chk_fmt(buf, buf_size, msg, ...) chk_impl_fmt##__VA_OPT__(_f)(buf, buf_size, msg __VA_OPT__(, ) __VA_ARGS__)
