#include <emscripten/html5.h>

#include <GLES3/gl3.h>
#include "emscripten/html5_webgl.h"

#define GRAPHICS_API_OPENGL_ES3
#define RLGL_IMPLEMENTATION
#include "raylib/rlgl.h"

#define RAYMATH_IMPLEMENTATION
#include "raylib/raymath.h"

#include "citra.h"
#include "ui_header.h"

app_state state = {.window = {.width = 0, .height = 0}};

int main(void) {
    // Initialize state
    emscripten_get_element_css_size(CANVAS_SELECTOR, &state.window.width, &state.window.height);
    emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, false, _emsc_size_changed);

    // Initialize WebGL context attributes
    EmscriptenWebGLContextAttributes attrs;
    emscripten_webgl_init_context_attributes(&attrs);
    attrs.alpha = EM_TRUE;
    attrs.depth = EM_TRUE;
    attrs.stencil = EM_FALSE;
    attrs.antialias = EM_TRUE;

    // Create WebGL context
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_create_context(CANVAS_SELECTOR, &attrs);
    emscripten_webgl_make_context_current(ctx);

    // Load OpenGL extensions
    rlLoadExtensions(emscripten_webgl_get_proc_address);

    // RLGL Initialization
    rlglInit(state.window.width, state.window.height);
    rlViewport(0, 0, state.window.width, state.window.height);
    rlMatrixMode(RL_PROJECTION);
    rlLoadIdentity();
    rlOrtho(0, state.window.width, state.window.height, 0, 0.0f, 1.0f);
    rlMatrixMode(RL_MODELVIEW);
    rlLoadIdentity();

    rlClearColor(40, 40, 40, 255);  // Define clear color
    rlEnableDepthTest();

    emscripten_request_animation_frame_loop(draw, 0);

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
