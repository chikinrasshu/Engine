#include <chk/opengl/opengl.h>

#include <chk/common/log.h>

bool chk_opengl_init(chk_opengl_load_t load) {
    bool result = false;

    s32 version = gladLoadGL((GLADloadfunc)load);
    if (version) {
        result = true;
        chk_log_info("Loaded OpenGL %d.%d", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
    } else {
        chk_log_error("Failed to load OpenGL");
    }

    return result;
}

bool chk_opengl_terminate(void) {
    chk_log_info("Terminated OpenGL");
    return true;
}
