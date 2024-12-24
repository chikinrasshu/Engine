#include <chk/workbench/workbench.h>

typedef struct chk_engine_data {
    chk_hsl_t bg_color;

    s32 vx, vy;
} chk_engine_data_t;

void on_frame(chk_window_t *window, void *user_ptr) {
    chk_engine_data_t *data = user_ptr;

#if 0
    chk_window_set_pos(window, window->data.x + data->vx, window->data.y + data->vy);
    if (window->data.x < 0 || window->data.x + window->data.w > 1920) { data->vx = -data->vx; }
    if (window->data.y < 0 || window->data.y + window->data.h > 1080) { data->vy = -data->vy; }

    chk_window_set_size(window, window->data.w + data->vx, window->data.h + data->vy);
#endif

    if (window->input.kbd.keys[CHK_KBD_KEY_ENTER].is_pressed) {
        chk_window_set_fullscreen(window, !window->is.fullscreen);
    }

    data->bg_color.h += 45.f * window->data.delta_time;
    if (data->bg_color.h > 360.0f) { data->bg_color.h -= 360.0f; }
    chk_rgb_t bg = chk_hsl_to_rgb(data->bg_color);

    glClearColor(bg.r, bg.g, bg.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv) {
    chk_window_t      window      = {0};
    chk_renderer_t    renderer    = {0};
    chk_engine_data_t engine_data = {0};

    engine_data.bg_color = chk_rgb_to_hsl((chk_rgb_t){1.f, 0.f, 0.f});

    engine_data.vx = 2;
    engine_data.vy = 1;

    // window.is.fullscreen = true;

    s32 result = 1;
    if (chk_window_init(&window, 800, 600, "Workbench")) {
        if (chk_renderer_init(&renderer)) {
            window.callbacks.user_ptr = &engine_data;
            window.callbacks.on_frame = on_frame;

            result = chk_window_run(&window);
            chk_window_destroy(&window);
        }
    }

    return result;
}
