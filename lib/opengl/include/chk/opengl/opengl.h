#pragma once

#include <chk/opengl/loader.h>

#include <chk/common/types.h>

// typedef void (*GLADapiproc)(void);
// typedef GLADapiproc (*GLADloadfunc)(const char *name);

typedef void (*chk_opengl_proc_t)(void);
typedef chk_opengl_proc_t (*chk_opengl_load_t)(const char *name);

bool chk_opengl_init(chk_opengl_load_t load);
bool chk_opengl_terminate(void);
