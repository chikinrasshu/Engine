#pragma once

#include <chk/common/types.h>

typedef struct chk_renderer {
    s32 xd;
} chk_renderer_t;

void chk_renderer_init(chk_renderer_t *renderer);
void chk_renderer_destroy(chk_renderer_t *renderer);

void chk_renderer_push_quad(chk_renderer_t *renderer, f32 x, f32 y, f32 w, f32 h);
void chk_renderer_push_triangle(chk_renderer_t *renderer);