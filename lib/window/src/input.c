#include <chk/window/window.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

static size_t g_chk_window_lut_glfw_to_key[GLFW_KEY_LAST + 1];
static size_t g_chk_window_lut_glfw_to_btn[GLFW_MOUSE_BUTTON_LAST + 1];

void chk_window_cb_on_mouse_pos(GLFWwindow *handle, f64 x, f64 y);
void chk_window_cb_on_mouse_btn(GLFWwindow *handle, s32 btn, s32 action, s32 mods);
void chk_window_cb_on_kbd_key(GLFWwindow *handle, s32 key, s32 scan_code, s32 action, s32 mods);

bool chk_window_init_input(chk_window_t *window) {
    if (!window) { return false; }

    // Initialize LUT for GLFW->Kbd_Key
    g_chk_window_lut_glfw_to_key[GLFW_KEY_SPACE]         = CHK_KBD_KEY_SPACE;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_APOSTROPHE]    = CHK_KBD_KEY_APOSTROPHE;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_COMMA]         = CHK_KBD_KEY_COMMA;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_MINUS]         = CHK_KBD_KEY_MINUS;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_PERIOD]        = CHK_KBD_KEY_PERIOD;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_SLASH]         = CHK_KBD_KEY_SLASH;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_0]             = CHK_KBD_KEY_0;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_1]             = CHK_KBD_KEY_1;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_2]             = CHK_KBD_KEY_2;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_3]             = CHK_KBD_KEY_3;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_4]             = CHK_KBD_KEY_4;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_5]             = CHK_KBD_KEY_5;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_6]             = CHK_KBD_KEY_6;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_7]             = CHK_KBD_KEY_7;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_8]             = CHK_KBD_KEY_8;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_9]             = CHK_KBD_KEY_9;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_SEMICOLON]     = CHK_KBD_KEY_SEMICOLON;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_EQUAL]         = CHK_KBD_KEY_EQUAL;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_A]             = CHK_KBD_KEY_A;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_B]             = CHK_KBD_KEY_B;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_C]             = CHK_KBD_KEY_C;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_D]             = CHK_KBD_KEY_D;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_E]             = CHK_KBD_KEY_E;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_F]             = CHK_KBD_KEY_F;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_G]             = CHK_KBD_KEY_G;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_H]             = CHK_KBD_KEY_H;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_I]             = CHK_KBD_KEY_I;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_J]             = CHK_KBD_KEY_J;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_K]             = CHK_KBD_KEY_K;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_L]             = CHK_KBD_KEY_L;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_M]             = CHK_KBD_KEY_M;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_N]             = CHK_KBD_KEY_N;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_O]             = CHK_KBD_KEY_O;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_P]             = CHK_KBD_KEY_P;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_Q]             = CHK_KBD_KEY_Q;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_R]             = CHK_KBD_KEY_R;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_S]             = CHK_KBD_KEY_S;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_T]             = CHK_KBD_KEY_T;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_U]             = CHK_KBD_KEY_U;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_V]             = CHK_KBD_KEY_V;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_W]             = CHK_KBD_KEY_W;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_X]             = CHK_KBD_KEY_X;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_Y]             = CHK_KBD_KEY_Y;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_Z]             = CHK_KBD_KEY_Z;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_LEFT_BRACKET]  = CHK_KBD_KEY_LEFT_BRACKET;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_BACKSLASH]     = CHK_KBD_KEY_BACKSLASH;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_RIGHT_BRACKET] = CHK_KBD_KEY_RIGHT_BRACKET;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_GRAVE_ACCENT]  = CHK_KBD_KEY_GRAVE_ACCENT;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_WORLD_1]       = CHK_KBD_KEY_WORLD_1;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_WORLD_2]       = CHK_KBD_KEY_WORLD_2;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_ESCAPE]        = CHK_KBD_KEY_ESCAPE;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_ENTER]         = CHK_KBD_KEY_ENTER;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_TAB]           = CHK_KBD_KEY_TAB;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_BACKSPACE]     = CHK_KBD_KEY_BACKSPACE;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_INSERT]        = CHK_KBD_KEY_INSERT;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_DELETE]        = CHK_KBD_KEY_DELETE;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_RIGHT]         = CHK_KBD_KEY_RIGHT;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_LEFT]          = CHK_KBD_KEY_LEFT;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_DOWN]          = CHK_KBD_KEY_DOWN;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_UP]            = CHK_KBD_KEY_UP;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_PAGE_UP]       = CHK_KBD_KEY_PAGE_UP;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_PAGE_DOWN]     = CHK_KBD_KEY_PAGE_DOWN;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_HOME]          = CHK_KBD_KEY_HOME;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_END]           = CHK_KBD_KEY_END;
    g_chk_window_lut_glfw_to_key[GLFW_KEY_CAPS_LOCK]     = CHK_KBD_KEY_CAPS_LOCK;

    // Initialize LUT for GLFW->Mouse_Btn
    g_chk_window_lut_glfw_to_btn[GLFW_MOUSE_BUTTON_1] = CHK_MOUSE_BTN_1;
    g_chk_window_lut_glfw_to_btn[GLFW_MOUSE_BUTTON_2] = CHK_MOUSE_BTN_2;
    g_chk_window_lut_glfw_to_btn[GLFW_MOUSE_BUTTON_3] = CHK_MOUSE_BTN_3;
    g_chk_window_lut_glfw_to_btn[GLFW_MOUSE_BUTTON_4] = CHK_MOUSE_BTN_4;
    g_chk_window_lut_glfw_to_btn[GLFW_MOUSE_BUTTON_5] = CHK_MOUSE_BTN_5;
    g_chk_window_lut_glfw_to_btn[GLFW_MOUSE_BUTTON_6] = CHK_MOUSE_BTN_6;
    g_chk_window_lut_glfw_to_btn[GLFW_MOUSE_BUTTON_7] = CHK_MOUSE_BTN_7;
    g_chk_window_lut_glfw_to_btn[GLFW_MOUSE_BUTTON_8] = CHK_MOUSE_BTN_8;

    window->input = (chk_input_t){0};
    glfwSetCursorPosCallback(window->impl, chk_window_cb_on_mouse_pos);
    glfwSetMouseButtonCallback(window->impl, chk_window_cb_on_mouse_btn);
    glfwSetKeyCallback(window->impl, chk_window_cb_on_kbd_key);

    return true;
}

bool chk_window_destroy_input(chk_window_t *window) {
    if (!window) { return false; }

    window->input = (chk_input_t){0};

    return true;
}

bool chk_window_update_input(chk_window_t *window) {
    if (!window) { return false; }

    for (size_t i = 0; i < sizeof(window->input.kbd.keys); ++i) {
        window->input.kbd.keys[i].is_pressed  = false;
        window->input.kbd.keys[i].is_released = false;
        window->input.kbd.keys[i].is_repeated = false;
    }

    for (size_t i = 0; i < sizeof(window->input.mouse.btns); ++i) {
        window->input.mouse.btns[i].is_pressed  = false;
        window->input.mouse.btns[i].is_released = false;
        window->input.mouse.btns[i].is_repeated = false;
    }

    return true;
}

void chk_window_cb_on_mouse_pos(GLFWwindow *handle, f64 x, f64 y) {
    chk_window_t *window = (chk_window_t *)glfwGetWindowUserPointer(handle);
    if (window) {
        window->input.mouse.x = (f32)x;
        window->input.mouse.y = (f32)y;
    }
}

void chk_window_cb_on_mouse_btn(GLFWwindow *handle, s32 btn, s32 action, s32 mods) {
    chk_window_t *window = (chk_window_t *)glfwGetWindowUserPointer(handle);
    if (window) {
        chk_mouse_btn_t index = g_chk_window_lut_glfw_to_btn[btn];

        switch (action) {
            case GLFW_PRESS: {
                window->input.mouse.btns[index].is_down    = true;
                window->input.mouse.btns[index].is_pressed = true;
            } break;

            case GLFW_RELEASE: {
                window->input.mouse.btns[index].is_down     = false;
                window->input.mouse.btns[index].is_released = true;
            } break;

            case GLFW_REPEAT: {
                window->input.mouse.btns[index].is_pressed  = true;
                window->input.mouse.btns[index].is_repeated = true;
            } break;
        }
    }
}

void chk_window_cb_on_kbd_key(GLFWwindow *handle, s32 key, s32 scan_code, s32 action, s32 mods) {
    chk_window_t *window = (chk_window_t *)glfwGetWindowUserPointer(handle);
    if (window) {
        chk_kbd_key_t index = g_chk_window_lut_glfw_to_key[key];

        switch (action) {
            case GLFW_PRESS: {
                window->input.kbd.keys[index].is_down    = true;
                window->input.kbd.keys[index].is_pressed = true;
            } break;

            case GLFW_RELEASE: {
                window->input.kbd.keys[index].is_down     = false;
                window->input.kbd.keys[index].is_released = true;
            } break;

            case GLFW_REPEAT: {
                window->input.kbd.keys[index].is_pressed  = true;
                window->input.kbd.keys[index].is_repeated = true;
            } break;
        }
    }
}