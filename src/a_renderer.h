#ifndef A_RENDERER_H
#define A_RENDERER_H

#include "defs.h"
#include "a_window.h"

extern void ctxInit(a_Window* window, char maj, char min);

extern void ctxPrepare();
extern void ctxClear(vec3 rgba);

#endif