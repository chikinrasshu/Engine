#pragma once

#include <chk/common/types.h>

typedef enum chk_kbd_key {
    CHK_KBD_KEY_UNKNOWN       = 0,
    CHK_KBD_KEY_SPACE         = ' ',
    CHK_KBD_KEY_APOSTROPHE    = '\'',
    CHK_KBD_KEY_COMMA         = ',',
    CHK_KBD_KEY_MINUS         = '-',
    CHK_KBD_KEY_PERIOD        = '.',
    CHK_KBD_KEY_SLASH         = '/',
    CHK_KBD_KEY_0             = '0',
    CHK_KBD_KEY_1             = '1',
    CHK_KBD_KEY_2             = '2',
    CHK_KBD_KEY_3             = '3',
    CHK_KBD_KEY_4             = '4',
    CHK_KBD_KEY_5             = '5',
    CHK_KBD_KEY_6             = '6',
    CHK_KBD_KEY_7             = '7',
    CHK_KBD_KEY_8             = '8',
    CHK_KBD_KEY_9             = '9',
    CHK_KBD_KEY_SEMICOLON     = ';',
    CHK_KBD_KEY_EQUAL         = '=',
    CHK_KBD_KEY_A             = 'A',
    CHK_KBD_KEY_B             = 'B',
    CHK_KBD_KEY_C             = 'C',
    CHK_KBD_KEY_D             = 'D',
    CHK_KBD_KEY_E             = 'E',
    CHK_KBD_KEY_F             = 'F',
    CHK_KBD_KEY_G             = 'G',
    CHK_KBD_KEY_H             = 'H',
    CHK_KBD_KEY_I             = 'I',
    CHK_KBD_KEY_J             = 'J',
    CHK_KBD_KEY_K             = 'K',
    CHK_KBD_KEY_L             = 'L',
    CHK_KBD_KEY_M             = 'M',
    CHK_KBD_KEY_N             = 'N',
    CHK_KBD_KEY_O             = 'O',
    CHK_KBD_KEY_P             = 'P',
    CHK_KBD_KEY_Q             = 'Q',
    CHK_KBD_KEY_R             = 'R',
    CHK_KBD_KEY_S             = 'S',
    CHK_KBD_KEY_T             = 'T',
    CHK_KBD_KEY_U             = 'U',
    CHK_KBD_KEY_V             = 'V',
    CHK_KBD_KEY_W             = 'W',
    CHK_KBD_KEY_X             = 'X',
    CHK_KBD_KEY_Y             = 'Y',
    CHK_KBD_KEY_Z             = 'Z',
    CHK_KBD_KEY_LEFT_BRACKET  = '[',
    CHK_KBD_KEY_BACKSLASH     = '\\',
    CHK_KBD_KEY_RIGHT_BRACKET = ']',
    CHK_KBD_KEY_GRAVE_ACCENT  = '`',
    CHK_KBD_KEY_WORLD_1,
    CHK_KBD_KEY_WORLD_2,
    CHK_KBD_KEY_ESCAPE,
    CHK_KBD_KEY_ENTER,
    CHK_KBD_KEY_TAB,
    CHK_KBD_KEY_BACKSPACE,
    CHK_KBD_KEY_INSERT,
    CHK_KBD_KEY_DELETE,
    CHK_KBD_KEY_RIGHT,
    CHK_KBD_KEY_LEFT,
    CHK_KBD_KEY_DOWN,
    CHK_KBD_KEY_UP,
    CHK_KBD_KEY_PAGE_UP,
    CHK_KBD_KEY_PAGE_DOWN,
    CHK_KBD_KEY_HOME,
    CHK_KBD_KEY_END,
    CHK_KBD_KEY_CAPS_LOCK,

    CHK_KBD_KEY_COUNT
} chk_kbd_key_t;

typedef enum chk_mouse_btn {
    CHK_MOUSE_BTN_UNKNOWN = 0,
    CHK_MOUSE_BTN_1,
    CHK_MOUSE_BTN_2,
    CHK_MOUSE_BTN_3,
    CHK_MOUSE_BTN_4,
    CHK_MOUSE_BTN_5,
    CHK_MOUSE_BTN_6,
    CHK_MOUSE_BTN_7,
    CHK_MOUSE_BTN_8,

    CHK_MOUSE_BTN_COUNT,

    CHK_MOUSE_BTN_LEFT   = CHK_MOUSE_BTN_1,
    CHK_MOUSE_BTN_RIGHT  = CHK_MOUSE_BTN_2,
    CHK_MOUSE_BTN_MIDDLE = CHK_MOUSE_BTN_3,
} chk_mouse_btn_t;

typedef struct chk_key {
    u8 is_down     : 1;
    u8 is_pressed  : 1;
    u8 is_released : 1;
    u8 is_repeated : 1;
} chk_key_t;
typedef chk_key_t chk_btn_t;

typedef struct chk_kbd {
    chk_key_t keys[CHK_KBD_KEY_COUNT];
} chk_kbd_t;

typedef struct chk_mouse {
    chk_btn_t btns[CHK_MOUSE_BTN_COUNT];

    f32 x, y;
    f32 dx, dy;
    f32 sx, sy;
} chk_mouse_t;

typedef struct chk_input {
    chk_kbd_t   kbd;
    chk_mouse_t mouse;
} chk_input_t;
