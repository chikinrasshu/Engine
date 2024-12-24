#include <chk/window/window.h>

#include <chk/common/log.h>
#include <chk/opengl/opengl.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#if defined(_WIN32)
#    include <chk/window/win32/window.h>
#endif

void chk_window_cb_on_error(s32 code, const char *msg);
void chk_window_cb_on_close(GLFWwindow *impl);
void chk_window_cb_on_frame(GLFWwindow *impl);
void chk_window_cb_on_pos(GLFWwindow *impl, s32 x, s32 y);
void chk_window_cb_on_size(GLFWwindow *impl, s32 w, s32 h);
void chk_window_cb_on_fb_size(GLFWwindow *impl, s32 w, s32 h);
void chk_window_cb_on_dpi(GLFWwindow *impl, f32 x, f32 y);
void chk_window_cb_on_focus(GLFWwindow *impl, s32 focused);
void chk_window_cb_on_hover(GLFWwindow *impl, s32 entered);
void chk_window_cb_on_min(GLFWwindow *impl, s32 minimized);
void chk_window_cb_on_max(GLFWwindow *impl, s32 maximized);

static s32 g_chk_window_count = 0;

bool chk_window_check_init() {
    if (!g_chk_window_count) {
        glfwSetErrorCallback(chk_window_cb_on_error);
        if (!glfwInit()) {
            chk_log_error("Failed to initialize GLFW");
            return false;
        }
    }
    return true;
}

bool chk_window_init(chk_window_t *window, s32 w, s32 h, const char *caption) {
    if (!window) { return false; }

    if (chk_window_check_init()) {
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

        window->impl = glfwCreateWindow(w, h, caption, NULL, NULL);
        if (window->impl) {
            glfwMakeContextCurrent(window->impl);
            if (chk_opengl_init(glfwGetProcAddress)) {
                // Per platform initialization
#if defined(_WIN32)
                chk_window_win32_init(window);
#endif

                glfwSetWindowUserPointer(window->impl, window);
                glfwSetWindowCloseCallback(window->impl, chk_window_cb_on_close);
                glfwSetWindowRefreshCallback(window->impl, chk_window_cb_on_frame);
                glfwSetWindowPosCallback(window->impl, chk_window_cb_on_pos);
                glfwSetWindowSizeCallback(window->impl, chk_window_cb_on_size);
                glfwSetFramebufferSizeCallback(window->impl, chk_window_cb_on_fb_size);
                glfwSetWindowContentScaleCallback(window->impl, chk_window_cb_on_dpi);
                glfwSetWindowFocusCallback(window->impl, chk_window_cb_on_focus);
                glfwSetCursorEnterCallback(window->impl, chk_window_cb_on_hover);
                glfwSetWindowIconifyCallback(window->impl, chk_window_cb_on_min);
                glfwSetWindowMaximizeCallback(window->impl, chk_window_cb_on_max);

                window->data.x    = 0;
                window->data.y    = 0;
                window->data.w    = w;
                window->data.h    = h;
                window->data.fb_w = w;
                window->data.fb_h = h;
                window->data.dpi  = 1.0f;

                f32 dpi_x, dpi_y;
                glfwGetWindowPos(window->impl, &window->data.x, &window->data.y);
                glfwGetWindowSize(window->impl, &window->data.w, &window->data.h);
                glfwGetFramebufferSize(window->impl, &window->data.fb_w, &window->data.fb_h);
                glfwGetWindowContentScale(window->impl, &dpi_x, &dpi_y);
                window->data.dpi = (dpi_x + dpi_y) * 0.5f;

                glfwShowWindow(window->impl);
                window->is.running = true;
                ++g_chk_window_count;
            } else {
                glfwDestroyWindow(window->impl);
                window->impl = NULL;
            }
        } else {
            chk_log_error("Failed to create window");
        }
    } else {
        chk_log_error("Failed to initialize GLFW");
    }

    return window->impl && window->is.running;
}

bool chk_window_destroy(chk_window_t *window) {
    if (!window) { return false; }

    if (window->impl) {

#if defined(_WIN32)
        chk_window_win32_terminate(window);
#endif

        glfwDestroyWindow(window->impl);
    }

    *window = (chk_window_t){0};

    --g_chk_window_count;
    if (!g_chk_window_count) { glfwTerminate(); }

    return true;
}

bool chk_window_step(chk_window_t *window, bool process_events) {
    if (!window) { return false; }

    if (window->is.running) {
        glfwMakeContextCurrent(window->impl);

        if (window->callbacks.on_frame) { window->callbacks.on_frame(window, window->callbacks.user_ptr); }

        if (process_events) { glfwPollEvents(); }
        glfwSwapBuffers(window->impl);

        window->data.current_time = glfwGetTime();
        window->data.delta_time   = window->data.current_time - window->data.last_time;
        window->data.last_time    = window->data.current_time;

        window->changed = (chk_window_changed_t){0};
    }
    return window->is.running;
}

bool chk_window_run(chk_window_t *window) {
    if (!window) { return false; }
    bool result = false;

    if (window->callbacks.on_open) { window->callbacks.on_open(window, window->callbacks.user_ptr); }

    while (window->is.running) { result = chk_window_step(window, true); }

    if (window->callbacks.on_close) { window->callbacks.on_close(window, window->callbacks.user_ptr); }

    return result;
}

void chk_window_cb_on_error(s32 code, const char *msg) { chk_log_error("GLFW Error %d: %s", code, msg); }

void chk_window_cb_on_close(GLFWwindow *impl) {
    chk_window_t *window = (chk_window_t *)glfwGetWindowUserPointer(impl);
    if (window) { window->is.running = false; }
}

void chk_window_cb_on_frame(GLFWwindow *impl) {
    chk_window_t *window = (chk_window_t *)glfwGetWindowUserPointer(impl);
    if (window) { chk_window_step(window, false); }
}

void chk_window_cb_on_pos(GLFWwindow *impl, s32 x, s32 y) {
    chk_window_t *window = (chk_window_t *)glfwGetWindowUserPointer(impl);
    if (window) {
        window->data.x      = x;
        window->data.y      = y;
        window->changed.pos = true;
        if (window->callbacks.on_pos) { window->callbacks.on_pos(window, window->callbacks.user_ptr); }
    }
}

void chk_window_cb_on_size(GLFWwindow *impl, s32 w, s32 h) {
    chk_window_t *window = (chk_window_t *)glfwGetWindowUserPointer(impl);
    if (window) {
        window->data.w       = w;
        window->data.h       = h;
        window->changed.size = true;
        if (window->callbacks.on_size) { window->callbacks.on_size(window, window->callbacks.user_ptr); }
    }
}

void chk_window_cb_on_fb_size(GLFWwindow *impl, s32 w, s32 h) {
    chk_window_t *window = (chk_window_t *)glfwGetWindowUserPointer(impl);
    if (window) {
        window->data.fb_w       = w;
        window->data.fb_h       = h;
        window->changed.fb_size = true;
        if (window->callbacks.on_fb_size) { window->callbacks.on_fb_size(window, window->callbacks.user_ptr); }

        glViewport(0, 0, w, h);
    }
}

void chk_window_cb_on_dpi(GLFWwindow *impl, f32 x, f32 y) {
    chk_window_t *window = (chk_window_t *)glfwGetWindowUserPointer(impl);
    if (window) {
        window->data.dpi    = (x + y) * 0.5f;
        window->changed.dpi = true;
        if (window->callbacks.on_dpi) { window->callbacks.on_dpi(window, window->callbacks.user_ptr); }
    }
}

void chk_window_cb_on_focus(GLFWwindow *impl, s32 focused) {
    chk_window_t *window = (chk_window_t *)glfwGetWindowUserPointer(impl);
    if (window) {
        window->is.focused    = !!focused;
        window->changed.focus = true;
        if (window->callbacks.on_focus) { window->callbacks.on_focus(window, window->callbacks.user_ptr); }
    }
}

void chk_window_cb_on_hover(GLFWwindow *impl, s32 entered) {
    chk_window_t *window = (chk_window_t *)glfwGetWindowUserPointer(impl);
    if (window) {
        window->is.hovered    = !!entered;
        window->changed.hover = true;
        if (window->callbacks.on_hover) { window->callbacks.on_hover(window, window->callbacks.user_ptr); }
    }
}

void chk_window_cb_on_min(GLFWwindow *impl, s32 minimized) {
    chk_window_t *window = (chk_window_t *)glfwGetWindowUserPointer(impl);
    if (window) {
        window->is.minimized   = !!minimized;
        window->changed.minmax = true;
        if (window->callbacks.on_minmax) { window->callbacks.on_minmax(window, window->callbacks.user_ptr); }
    }
}

void chk_window_cb_on_max(GLFWwindow *impl, s32 maximized) {
    chk_window_t *window = (chk_window_t *)glfwGetWindowUserPointer(impl);
    if (window) {
        window->is.maximized   = !!maximized;
        window->changed.minmax = true;
        if (window->callbacks.on_minmax) { window->callbacks.on_minmax(window, window->callbacks.user_ptr); }
    }
}
