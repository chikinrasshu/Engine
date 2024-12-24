#include <chk/workbench/workbench.h>

#include <chk/opengl/gl.h>

void on_frame(chk_window_t *window, void *user_ptr) {
    // glViewport(0, 0, window->data.fb_w, window->data.fb_h);
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv) {
    chk_window_t window = {0};

    s32 result = 1;
    if (chk_window_init(&window, 800, 600, "Workbench")) {
        window.callbacks.on_frame = on_frame;

        result = chk_window_run(&window);
        chk_window_destroy(&window);
    }

    return result;
}
