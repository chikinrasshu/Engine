#pragma once

#include <chk/common/types.h>

typedef struct chk_window chk_window_t;
typedef void (*chk_window_callback_t)(chk_window_t *window, void *user_ptr);

typedef struct chk_window_data {
    s32 x, y, w, h;
    s32 fb_w, fb_h;
    f32 dpi;

    f64 current_time;
    f64 last_time;
    f64 delta_time;
} chk_window_data_t;

typedef struct chk_window_state {
    u32 running    : 1;
    u32 focused    : 1;
    u32 hovered    : 1;
    u32 minimized  : 1;
    u32 maximized  : 1;
    u32 fullscreen : 1;
} chk_window_state_t;

typedef struct chk_window_changed {
    u32 pos     : 1;
    u32 size    : 1;
    u32 fb_size : 1;
    u32 dpi     : 1;

    u32 focus      : 1;
    u32 hover      : 1;
    u32 minmax     : 1;
    u32 fullscreen : 1;
} chk_window_changed_t;

typedef struct chk_window_callbacks {
    void *user_ptr;

    chk_window_callback_t on_pos;
    chk_window_callback_t on_size;
    chk_window_callback_t on_fb_size;
    chk_window_callback_t on_dpi;

    chk_window_callback_t on_focus;
    chk_window_callback_t on_hover;
    chk_window_callback_t on_minmax;
    chk_window_callback_t on_fullscreen;

    chk_window_callback_t on_open;
    chk_window_callback_t on_close;
    chk_window_callback_t on_frame;
} chk_window_callbacks_t;

typedef struct chk_window {
    chk_window_data_t      data;
    chk_window_state_t     is;
    chk_window_changed_t   changed;
    chk_window_callbacks_t callbacks;

    void *impl;
} chk_window_t;

bool chk_window_init(chk_window_t *window, s32 w, s32 h, const char *caption);
bool chk_window_destroy(chk_window_t *window);
bool chk_window_run(chk_window_t *window);
