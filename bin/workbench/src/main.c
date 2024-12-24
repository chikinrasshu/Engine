#include <chk/workbench/workbench.h>

#include <chk/opengl/opengl.h>
#include <chk/renderer/color.h>

typedef struct chk_engine_data {
    chk_hsl_t bg_color;
} chk_engine_data_t;

void on_frame(chk_window_t *window, void *user_ptr) {
    chk_engine_data_t *data = user_ptr;

    data->bg_color.h += 45.f * window->data.delta_time;
    if (data->bg_color.h > 360.0f) { data->bg_color.h -= 360.0f; }
    chk_rgb_t bg = chk_hsl_to_rgb(data->bg_color);

    glClearColor(bg.r, bg.g, bg.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv) {
    chk_window_t      window      = {0};
    chk_engine_data_t engine_data = {0};

    engine_data.bg_color = chk_rgb_to_hsl((chk_rgb_t){1.f, 0.f, 0.f});

    s32 result = 1;
    if (chk_window_init(&window, 800, 600, "Workbench")) {
        window.callbacks.user_ptr = &engine_data;
        window.callbacks.on_frame = on_frame;

        result = chk_window_run(&window);
        chk_window_destroy(&window);
    }

    return result;
}
