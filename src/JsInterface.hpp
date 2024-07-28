#pragma once

#include "state-core.h"
#include "state-sdl.h"
#include <functional>

//Guard for JS
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/bind.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

class JsInterface {
public:
	std::function<bool()>                     doInit;
    std::function<void(int, int)>             setWindowSize;
    std::function<void(const std::string & )> setData;
    std::function<std::string()>              getData;
    std::function<std::string()>              getClipboard;
    std::function<std::string()>              getURL;

    std::function<bool()> mainLoop;

    bool init(StateSDL & stateSDL, StateCore & stateCore);

private:
    // setWindowSize
    int lastX = -1;
    int lastY = -1;

};
