#include "Constants.hpp"
#include "JsInterface.hpp"
#include "Renderer.hpp"
#include "build-timestamp.h"

#include "common.h"

#include "state-sdl.h"
#include "state-core.h"

#include "icons-font-awesome.h"

#include "imgui-extra/imgui_impl.h"

#include <SDL2/SDL.h>

#include <string>
#include <functional>
#include "JsInterface.hpp"

namespace {

//
// App Interface
//

JsInterface g_appInterface;

#ifdef __EMSCRIPTEN__

// need this wrapper of the main loop for the emscripten_set_main_loop_arg() call
void mainLoop(void *) {
    g_appInterface.mainLoop();
}


// These functions are used to pass data back and forth between the JS and the C++ code
// using the app interface

EMSCRIPTEN_BINDINGS(ggweb) {
    emscripten::function("doInit",        emscripten::optional_override([]() -> int                   { return g_appInterface.doInit(); }));
    emscripten::function("setWindowSize", emscripten::optional_override([](int sizeX, int sizeY)      { g_appInterface.setWindowSize(sizeX, sizeY); }));
    emscripten::function("setData",       emscripten::optional_override([](const std::string & input) { g_appInterface.setData(input); }));
    emscripten::function("getData",       emscripten::optional_override([]() -> std::string           { return g_appInterface.getData(); }));
    emscripten::function("getClipboard",  emscripten::optional_override([]() -> std::string           { return g_appInterface.getClipboard(); }));
    emscripten::function("getURL",        emscripten::optional_override([]() -> std::string           { return g_appInterface.getURL(); }));
}

#endif

}

Renderer g_renderer;

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    printf("Build time: %s\n", BUILD_TIMESTAMP);
    g_renderer.Initialize("Website thingy");
    // initialize the application interface
    if (!g_appInterface.init(g_renderer.GetStateSDL(), g_renderer.GetStateCore())) {
        fprintf(stderr, "Error: failed to initialize app interface.\n");
        return -4;
    }

#ifdef __EMSCRIPTEN__
    // main - emscripten
    {
        emscripten_set_main_loop_arg(mainLoop, NULL, 0, true);
    }
#else
    // main - native
    {
        g_appInterface.setWindowSize(g_renderer.GetStateSDL().windowX, g_renderer.GetStateSDL().windowY);

        if (!g_appInterface.doInit()) {
            printf("Error: failed to initialize\n");
            return -5;
        }

        // main loop
        while (true) {
            if (!g_appInterface.mainLoop()) {
                printf("Main loop exited\n");
                break;
            }

            // update window size
            {
                int sizeX = -1;
                int sizeY = -1;

                SDL_GetWindowSize(g_renderer.GetStateSDL().window, &sizeX, &sizeY);
                g_appInterface.setWindowSize(sizeX, sizeY);
            }
        }

        // cleanup
        {
        	g_renderer.Dispose();
        }
    }
#endif

    return 0;
}
