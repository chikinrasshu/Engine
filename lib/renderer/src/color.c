#include <chk/renderer/color.h>

#include <math.h>

chk_rgb_t chk_hsl_to_rgb(chk_hsl_t hsl) {
    chk_rgb_t result;

    f32 c = hsl.s * hsl.v;
    f32 x = c * (1 - fabs(fmod(hsl.h / 60, 2) - 1));
    f32 m = hsl.v - c;

    if (hsl.h < 60) {
        result.r = c;
        result.g = x;
        result.b = 0;
    } else if (hsl.h < 120) {
        result.r = x;
        result.g = c;
        result.b = 0;
    } else if (hsl.h < 180) {
        result.r = 0;
        result.g = c;
        result.b = x;
    } else if (hsl.h < 240) {
        result.r = 0;
        result.g = x;
        result.b = c;
    } else if (hsl.h < 300) {
        result.r = x;
        result.g = 0;
        result.b = c;
    } else {
        result.r = c;
        result.g = 0;
        result.b = x;
    }

    result.r += m;
    result.g += m;
    result.b += m;

    return result;
}

chk_hsl_t chk_rgb_to_hsl(chk_rgb_t rgb) {
    chk_hsl_t result;

    f32 max = fmax(rgb.r, fmax(rgb.g, rgb.b));
    f32 min = fmin(rgb.r, fmin(rgb.g, rgb.b));
    f32 c   = max - min;
    f32 h   = 0;

    if (c == 0) {
        h = 0;
    } else if (max == rgb.r) {
        h = fmod((rgb.g - rgb.b) / c, 6) * 60;
    } else if (max == rgb.g) {
        h = ((rgb.b - rgb.r) / c + 2) * 60;
    } else {
        h = ((rgb.r - rgb.g) / c + 4) * 60;
    }

    result.h = h;
    result.s = max == 0 ? 0 : c / max;
    result.v = max;

    return result;
}

chk_rgba_t chk_hsla_to_rgba(chk_hsla_t hsla) {
    chk_rgba_t result;
    result.rgb = chk_hsl_to_rgb(hsla.hsl);
    result.a   = hsla.a;
    return result;
}

chk_hsla_t chk_rgba_to_hsla(chk_rgba_t rgba) {
    chk_hsla_t result;
    result.hsl = chk_rgb_to_hsl(rgba.rgb);
    result.a   = rgba.a;
    return result;
}
