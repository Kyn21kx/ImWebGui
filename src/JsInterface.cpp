#include "JsInterface.hpp"
#include "Constants.hpp"
#include "imgui-extra/imgui_impl.h"
#include <SDL2/SDL_events.h>

bool JsInterface::init(StateSDL &stateSDL, StateCore &stateCore) {
	doInit = [&]() {
        stateCore.init(Constants::kFontScale);

        return true;
    };

    setWindowSize = [&](int sizeX, int sizeY) {
        if (lastX == sizeX && lastY == sizeY) {
            return;
        }

        lastX = sizeX;
        lastY = sizeY;

        SDL_SetWindowSize(stateSDL.window, sizeX, sizeY);

        stateCore.onWindowResize();
        stateCore.rendering.isAnimating = true;
    };

    setData = [&](const std::string & data) {
        printf("Received some data from the JS layer: %s\n", data.c_str());
    };

    getData = [&]() {
        const auto res = stateCore.dataDummy;
        stateCore.dataDummy.clear();
        return res;
    };

    getClipboard = [&]() {
        const auto res = stateCore.dataClipboard;
        stateCore.dataClipboard.clear();
        return res;
    };

    getURL = [&]() {
        const auto res = stateCore.dataURL;
        stateCore.dataURL.clear();
        return res;
    };

    mainLoop = [&]() {
        auto & nUpdates = stateCore.rendering.nUpdates;

        // framerate throtling when idle
        {
            --nUpdates;
            if (nUpdates < -30) nUpdates = 0;
            if (stateCore.rendering.isAnimating) nUpdates = std::max(nUpdates, 2);

            if (stateCore.isInitialized == false) {
                return true;
            }
        }

        // process window events
        {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                nUpdates = std::max(nUpdates, 5);
                ImGui_ProcessEvent(&event);
                if (event.type == SDL_QUIT) return false;
                if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(stateSDL.window)) return false;
            }
        }

        // update + render
        {
            if (stateCore.updatePre() == false) {
                return false;
            }

            if (nUpdates >= 0) {
                if (ImGui::NewFrame(stateSDL.window) == false) {
                    return false;
                }

                stateCore.render();

                if (ImGui::EndFrame(stateSDL.window) == false) {
                    return false;
                }
            }

            if (stateCore.updatePost() == false) {
                return false;
            }
        }

        return true;
    };

    return true;
}
