#include <chk/common/fmt.h>

#include <stdio.h>

s32 chk_impl_fmt_v(char *buf, size_t buf_size, const char *msg, va_list args) {
    va_list args_copy;
    va_copy(args_copy, args);
    s32 result = vsnprintf(buf, buf_size, msg, args_copy);
    va_end(args_copy);

    return result;
}

s32 chk_impl_fmt_f(char *buf, size_t buf_size, const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    s32 result = chk_impl_fmt_v(buf, buf_size, msg, args);
    va_end(args);

    return result;
}

s32 chk_impl_fmt(char *buf, size_t buf_size, const char *msg) {
    s32 result = snprintf(buf, buf_size, "%s", msg);
    return result;
}
