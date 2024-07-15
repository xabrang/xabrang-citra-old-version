#include <emscripten/html5.h>
#include "GLES3/gl3.h"

#ifndef CITRA_H
#define CITRA_H

typedef struct {
    struct {
        double width;
        double height;
    } window;
    GLint frambuffer;
} app_state;

#define CANVAS_SELECTOR "#canvas"

static EM_BOOL _emsc_size_changed(int event_type,
                                  const EmscriptenUiEvent* ui_event,
                                  void* user_data);
static EM_BOOL draw(double time, void* userdata);

#endif  // !CITRA_H
