#include <chk/window/win32/window.h>

#include <chk/common/log.h>

#ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include <dwmapi.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_NATIVE_INCLUDE_NONE
#include <GLFW/glfw3native.h>

typedef enum IMMERSIVE_HC_CACHE_MODE { IHCM_USE_CACHED_VALUE, IHCM_REFRESH } IMMERSIVE_HC_CACHE_MODE;

typedef enum PREFERRED_APP_MODE {
    PAM_DEFAULT,
    PAM_ALLOW_DARK,
    PAM_FORCE_DARK,
    PAM_FORCE_LIGHT,
    PAM_MAX
} PREFERRED_APP_MODE;

typedef enum WINDOWCOMPOSITIONATTRIB {
    WCA_UNDEFINED                     = 0,
    WCA_NCRENDERING_ENABLED           = 1,
    WCA_NCRENDERING_POLICY            = 2,
    WCA_TRANSITIONS_FORCEDISABLED     = 3,
    WCA_ALLOW_NCPAINT                 = 4,
    WCA_CAPTION_BUTTON_BOUNDS         = 5,
    WCA_NONCLIENT_RTL_LAYOUT          = 6,
    WCA_FORCE_ICONIC_REPRESENTATION   = 7,
    WCA_EXTENDED_FRAME_BOUNDS         = 8,
    WCA_HAS_ICONIC_BITMAP             = 9,
    WCA_THEME_ATTRIBUTES              = 10,
    WCA_NCRENDERING_EXILED            = 11,
    WCA_NCADORNMENTINFO               = 12,
    WCA_EXCLUDED_FROM_LIVEPREVIEW     = 13,
    WCA_VIDEO_OVERLAY_ACTIVE          = 14,
    WCA_FORCE_ACTIVEWINDOW_APPEARANCE = 15,
    WCA_DISALLOW_PEEK                 = 16,
    WCA_CLOAK                         = 17,
    WCA_CLOAKED                       = 18,
    WCA_ACCENT_POLICY                 = 19,
    WCA_FREEZE_REPRESENTATION         = 20,
    WCA_EVER_UNCLOAKED                = 21,
    WCA_VISUAL_OWNER                  = 22,
    WCA_HOLOGRAPHIC                   = 23,
    WCA_EXCLUDED_FROM_DDA             = 24,
    WCA_PASSIVEUPDATEMODE             = 25,
    WCA_USEDARKMODECOLORS             = 26,
    WCA_LAST                          = 27
} WINDOWCOMPOSITIONATTRIB;

typedef struct WINDOWCOMPOSITIONATTRIBDATA {
    WINDOWCOMPOSITIONATTRIB Attrib;
    PVOID                   pvData;
    SIZE_T                  cbData;
} WINDOWCOMPOSITIONATTRIBDATA;

// Fn pointer forward declarations

typedef void(WINAPI *fn_RtlGetNtVersionNumbers_t)(LPDWORD major, LPDWORD minor, LPDWORD build);
typedef BOOL(WINAPI *fn_SetWindowCompositionAttribute_t)(HWND hWnd, WINDOWCOMPOSITIONATTRIBDATA *);
typedef bool(WINAPI *fn_ShouldAppsUseDarkMode_t)();
typedef bool(WINAPI *fn_AllowDarkModeForWindow_t)(HWND hWnd, bool allow);
typedef bool(WINAPI *fn_AllowDarkModeForApp_t)(bool allow);
typedef void(WINAPI *fn_FlushMenuThemes_t)();
typedef void(WINAPI *fn_RefreshImmersiveColorPolicyState_t)();
typedef bool(WINAPI *fn_IsDarkModeAllowedForWindow_t)(HWND hWnd);
typedef bool(WINAPI *fn_GetIsImmersiveColorUsingHighContrast_t)(IMMERSIVE_HC_CACHE_MODE mode);
typedef HTHEME(WINAPI *fn_OpenNcThemeData_t)(HWND hWnd, LPCWSTR pszClassList);
typedef bool(WINAPI *fn_ShouldSystemUseDarkMode_t)();
typedef PREFERRED_APP_MODE(WINAPI *fn_SetPreferredAppMode_t)(PREFERRED_APP_MODE appMode);
typedef bool(WINAPI *fn_IsDarkModeAllowedForApp_t)();

typedef struct chk_window_winapi {
    fn_RtlGetNtVersionNumbers_t RtlGetNtVersionNumbers;

    fn_SetWindowCompositionAttribute_t        SetWindowCompositionAttribute;
    fn_ShouldAppsUseDarkMode_t                ShouldAppsUseDarkMode;
    fn_AllowDarkModeForWindow_t               AllowDarkModeForWindow;
    fn_AllowDarkModeForApp_t                  AllowDarkModeForApp;
    fn_FlushMenuThemes_t                      FlushMenuThemes;
    fn_RefreshImmersiveColorPolicyState_t     RefreshImmersiveColorPolicyState;
    fn_IsDarkModeAllowedForWindow_t           IsDarkModeAllowedForWindow;
    fn_GetIsImmersiveColorUsingHighContrast_t GetIsImmersiveColorUsingHighContrast;
    fn_OpenNcThemeData_t                      OpenNcThemeData;

    // 1903 18362
    fn_ShouldSystemUseDarkMode_t ShouldSystemUseDarkMode;
    fn_SetPreferredAppMode_t     SetPreferredAppMode;

    bool  dark_mode_supported;
    bool  dark_mode_enabled;
    DWORD build_number;
} chk_window_winapi;

static chk_window_winapi g_winapi = {0};

ULONG_PTR chk_window_win32_enable_visual_styles() {
    TCHAR     dir[MAX_PATH];
    ULONG_PTR activation_cookie  = FALSE;
    ACTCTX    activation_context = {sizeof(activation_context),
                                    ACTCTX_FLAG_RESOURCE_NAME_VALID | ACTCTX_FLAG_SET_PROCESS_DEFAULT |
                                        ACTCTX_FLAG_ASSEMBLY_DIRECTORY_VALID,
                                    TEXT("shell32.dll"),
                                    0,
                                    0,
                                    dir,
                                    (LPCTSTR)124};

    UINT cch = GetSystemDirectory(dir, sizeof(dir) / sizeof(*dir));
    if (cch >= sizeof(dir) / sizeof(*dir)) { return FALSE; /*shouldn't happen*/ }
    dir[cch] = TEXT('\0');
    ActivateActCtx(CreateActCtx(&activation_context), &activation_cookie);

    return activation_cookie;
}

bool chk_window_win32_check_build_number(DWORD build_number) {
    return (build_number == 17763 || // 1809
            build_number == 18362 || // 1903
            build_number == 18363 || // 1909
            build_number == 19041 || // 2004
            build_number == 19042 || // 20H2
            build_number == 19043 || // 21H1
            build_number == 19044 || // 21H2
            build_number == 19045    // 22H2
    );
}

bool chk_window_win32_allow_dark_mode_for_window(HWND handle, bool allow) {
    bool result = false;

    if (g_winapi.dark_mode_supported) { result = g_winapi.AllowDarkModeForWindow(handle, allow); }

    return result;
}

bool chk_window_win32_allow_dark_mode_for_app(bool allow) {
    bool result = false;

    if (g_winapi.AllowDarkModeForApp) {
        result = g_winapi.AllowDarkModeForApp(allow);
    } else if (g_winapi.SetPreferredAppMode) {
        result = g_winapi.SetPreferredAppMode(allow ? PAM_ALLOW_DARK : PAM_DEFAULT);
    }

    return result;
}

bool chk_window_win32_is_high_contrast() {
    bool result = false;

    HIGHCONTRASTW high_contrast = {sizeof(high_contrast)};
    if (SystemParametersInfoW(SPI_GETHIGHCONTRAST, sizeof(high_contrast), &high_contrast, FALSE)) {
        result = high_contrast.dwFlags & HCF_HIGHCONTRASTON;
    }

    return result;
}

void chk_window_win32_refresh_titlebar_theme_color(HWND handle) {
    BOOL dark = FALSE;
    if (g_winapi.IsDarkModeAllowedForWindow(handle) && g_winapi.ShouldAppsUseDarkMode() &&
        !chk_window_win32_is_high_contrast()) {
        dark = TRUE;
    }

    if (g_winapi.build_number < 18362) {
        SetPropW(handle, L"UseImmersiveDarkModeColors", (HANDLE)(INT_PTR)dark);
    } else if (g_winapi.SetWindowCompositionAttribute) {
        WINDOWCOMPOSITIONATTRIBDATA data = {WCA_USEDARKMODECOLORS, &dark, sizeof(dark)};
        g_winapi.SetWindowCompositionAttribute(handle, &data);
    }
}

bool chk_window_win32_is_color_scheme_change_msg(LPARAM lp) {
    bool result = false;

    if (lp && CompareStringOrdinal((LPCWCH)lp, -1, L"ImmersiveColorSet", -1, TRUE) == CSTR_EQUAL) {
        g_winapi.RefreshImmersiveColorPolicyState();
        result = true;
    }
    g_winapi.GetIsImmersiveColorUsingHighContrast(IHCM_REFRESH);

    return result;
}

bool chk_window_win32_is_color_scheme_change_msg_ex(UINT msg, LPARAM lp) {
    bool result = false;
    if (msg == WM_SETTINGCHANGE) { result = chk_window_win32_is_color_scheme_change_msg(lp); }
    return result;
}

// End Fn pointer forward declarations

LRESULT CALLBACK chk_window_win32_proc(HWND handle, UINT msg, WPARAM wp, LPARAM lp, UINT_PTR id, DWORD_PTR user_ptr) {
    LRESULT result = 0;

    chk_window_t *window = (chk_window_t *)user_ptr;

    switch (msg) {
        case WM_THEMECHANGED:
        case WM_SETTINGCHANGE: {
            if (chk_window_win32_is_color_scheme_change_msg(lp)) {
                bool old_mode = g_winapi.dark_mode_enabled;

                g_winapi.dark_mode_enabled = g_winapi.ShouldAppsUseDarkMode() && !chk_window_win32_is_high_contrast();

                if (old_mode != g_winapi.dark_mode_enabled) {
                    chk_window_win32_refresh_titlebar_theme_color(handle);
                    chk_log_info("Dark mode is %s", g_winapi.dark_mode_enabled ? "enabled" : "disabled");
                }
            }
        } break;
    }

    return DefSubclassProc(handle, msg, wp, lp);
}

bool chk_window_win32_init(chk_window_t *window) {
    if (!window) { return false; }
    HWND handle = glfwGetWin32Window(window->impl);

    bool result = false;
    chk_window_win32_enable_visual_styles();

    // Initialize the WinAPI private functions
    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
    if (ntdll) {
        g_winapi.RtlGetNtVersionNumbers = (fn_RtlGetNtVersionNumbers_t)GetProcAddress(ntdll, "RtlGetNtVersionNumbers");
        if (g_winapi.RtlGetNtVersionNumbers) {
            DWORD major, minor;
            g_winapi.RtlGetNtVersionNumbers(&major, &minor, &g_winapi.build_number);
            g_winapi.build_number &= ~0xF0000000;

            if (major == 10 && minor == 0 && chk_window_win32_check_build_number(g_winapi.build_number)) {
                HMODULE uxtheme = LoadLibraryExW(L"uxtheme.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
                if (uxtheme) {
                    g_winapi.OpenNcThemeData = (fn_OpenNcThemeData_t)GetProcAddress(uxtheme, MAKEINTRESOURCEA(49));
                    g_winapi.RefreshImmersiveColorPolicyState =
                        (fn_RefreshImmersiveColorPolicyState_t)GetProcAddress(uxtheme, MAKEINTRESOURCEA(104));
                    g_winapi.GetIsImmersiveColorUsingHighContrast =
                        (fn_GetIsImmersiveColorUsingHighContrast_t)GetProcAddress(uxtheme, MAKEINTRESOURCEA(106));
                    g_winapi.ShouldAppsUseDarkMode =
                        (fn_ShouldAppsUseDarkMode_t)GetProcAddress(uxtheme, MAKEINTRESOURCEA(132));
                    g_winapi.AllowDarkModeForWindow =
                        (fn_AllowDarkModeForWindow_t)GetProcAddress(uxtheme, MAKEINTRESOURCEA(133));

                    FARPROC ord135 = GetProcAddress(uxtheme, MAKEINTRESOURCEA(135));
                    if (g_winapi.build_number < 18362) {
                        g_winapi.AllowDarkModeForApp = (fn_AllowDarkModeForApp_t)ord135;
                    } else {
                        g_winapi.SetPreferredAppMode = (fn_SetPreferredAppMode_t)ord135;
                    }

                    HMODULE user32 = GetModuleHandleW(L"user32.dll");

                    g_winapi.IsDarkModeAllowedForWindow =
                        (fn_IsDarkModeAllowedForWindow_t)GetProcAddress(uxtheme, MAKEINTRESOURCEA(137));
                    g_winapi.SetWindowCompositionAttribute =
                        (fn_SetWindowCompositionAttribute_t)GetProcAddress(user32, "SetWindowCompositionAttribute");

                    if (g_winapi.OpenNcThemeData && g_winapi.RefreshImmersiveColorPolicyState &&
                        g_winapi.ShouldAppsUseDarkMode && g_winapi.AllowDarkModeForWindow &&
                        (g_winapi.AllowDarkModeForApp || g_winapi.SetPreferredAppMode) &&
                        g_winapi.IsDarkModeAllowedForWindow) {
                        g_winapi.dark_mode_supported = true;

                        chk_window_win32_allow_dark_mode_for_app(true);
                        g_winapi.RefreshImmersiveColorPolicyState();

                        g_winapi.dark_mode_enabled =
                            g_winapi.ShouldAppsUseDarkMode() && !chk_window_win32_is_high_contrast();

                        chk_log_debug("Dark mode is %s", g_winapi.dark_mode_supported ? "supported" : "unsupported");
                        chk_log_debug("Dark mode is %s", g_winapi.dark_mode_enabled ? "enabled" : "disabled");

                        SetWindowSubclass(handle, chk_window_win32_proc, 69, (DWORD_PTR)window);
                    } else {
                        chk_log_warn("Dark mode is unsupported in version %d.%d", major, minor);
                    }
                } else {
                    chk_log_error("Failed to load uxtheme.dll");
                }
            } else {
                chk_log_warn("Unsupported Windows 10 version %d.%d", major, minor);
            }
        } else {
            chk_log_error("Failed to get RtlGetNtVersionNumbers");
        }
    } else {
        chk_log_error("Failed to load ntdll.dll");
    }

    if (g_winapi.dark_mode_supported) {
        g_winapi.AllowDarkModeForWindow(handle, true);
        chk_window_win32_refresh_titlebar_theme_color(handle);
    }

    return result;
}

bool chk_window_win32_terminate(chk_window_t *window) {
    HWND handle = glfwGetWin32Window(window->impl);

    bool result = false;
    if (handle) {
        RemoveWindowSubclass(handle, chk_window_win32_proc, 69);
        result = true;
    }

    return result;
}
