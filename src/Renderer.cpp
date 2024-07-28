#include "Renderer.hpp"
#include "Constants.hpp"
#include "icons-font-awesome.h"
#include <SDL2/SDL.h>
#include <cassert>

void Renderer::Initialize(const std::string_view& windowName) {
	bool assertionRes = this->InitializeSDL(windowName);
	assert(assertionRes);
    // initialize SDL + ImGui
    {
        if (!this->m_stateSDL.initImGui(
                        Constants::kFontScale,
                        {
                            // add fonts to be loaded
                            { .filename = "fontawesome-webfont.ttf", .size = 14.0f* Constants::kFontScale, .merge = true, .rangeMin = ICON_MIN_FA, .rangeMax = ICON_MAX_FA, },
                            //{ .filename = "some-cool-font.ttf", .size = 14.0f*kFontScale, .merge = false, .rangeMin = ..., .rangeMax = ..., },
                        })) {
            fprintf(stderr, "Error: failed to initialize ImGui.\n");
            return;
        }
    }
}

bool Renderer::InitializeSDL(const std::string_view& windowName) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error: failed to initialize SDL. Reason: %s\n", SDL_GetError());
        return false;
	}

 	if (!this->m_stateSDL.initWindow(windowName.data())) {
       	//TODO: Add assert
        fprintf(stderr, "Error: failed to initialize SDL window.\n");
        return false;
    }

	return true;
}

StateCore& Renderer::GetStateCore() noexcept {
	return this->m_stateCore;
}

StateSDL& Renderer::GetStateSDL() noexcept {
	return this->m_stateSDL;
}

void Renderer::Dispose() noexcept {
	this->m_stateCore.deinitMain();
	this->m_stateSDL.deinitImGui();
	this->m_stateSDL.deinitWindow();
}
