#include "citra.h"
#include <GLES3/gl3.h>
#include <emscripten/html5.h>
#include "stdio.h"

int main(void) {
    // init state
    app_state state = {.window = {.width = 0, .height = 0}};

    emscripten_get_element_css_size(CANVAS_SELECTOR, &state.window.width, &state.window.height);
    emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, false, _emsc_size_changed);

    // Initialize WebGL context attributes
    EmscriptenWebGLContextAttributes attrs;
    emscripten_webgl_init_context_attributes(&attrs);
    attrs.alpha = EM_TRUE;
    attrs.depth = EM_TRUE;
    attrs.stencil = EM_FALSE;
    attrs.antialias = EM_TRUE;
    attrs.majorVersion = 2;

    // Create WebGL context
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_create_context(CANVAS_SELECTOR, &attrs);
    emscripten_webgl_make_context_current(ctx);
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &state.frambuffer);

    emscripten_request_animation_frame_loop(draw, &state);

    return 0;
}
static EM_BOOL _emsc_size_changed(int event_type,
                                  const EmscriptenUiEvent* ui_event,
                                  void* userdata) {
    (void)event_type;
    (void)ui_event;

    app_state* state = (app_state*)userdata;

    emscripten_get_element_css_size(CANVAS_SELECTOR, &state->window.width, &state->window.height);
    emscripten_set_canvas_element_size(CANVAS_SELECTOR, state->window.width, state->window.height);

    return EM_TRUE;
}

static EM_BOOL draw(double time, void* userdata) {
    (void)time;

    app_state* state = (app_state*)userdata;

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    emscripten_get_element_css_size(CANVAS_SELECTOR, &state->window.width, &state->window.height);
    printf("%f, %f\n", state->window.width, state->window.height);

    glFlush();

    return EM_TRUE;
}
