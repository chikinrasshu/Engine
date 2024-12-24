#pragma once

#include <chk/common/types.h>

typedef struct chk_rgb {
    f32 r, g, b;
} chk_rgb_t;

typedef struct chk_hsl {
    f32 h, s, v;
} chk_hsl_t;

typedef union chk_rgba {
    struct {
        chk_rgb_t rgb;
        f32       _a;
    };
    struct {
        f32 r, g, b, a;
    };
} chk_rgba_t;

typedef union chk_hsla {
    struct {
        chk_hsl_t hsl;
        f32       _a;
    };
    struct {
        f32 h, s, v, a;
    };
} chk_hsla_t;

chk_rgb_t chk_hsl_to_rgb(chk_hsl_t hsl);
chk_hsl_t chk_rgb_to_hsl(chk_rgb_t rgb);

chk_rgba_t chk_hsla_to_rgba(chk_hsla_t hsla);
chk_hsla_t chk_rgba_to_hsla(chk_rgba_t rgba);
