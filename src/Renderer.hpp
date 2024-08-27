#pragma once

#include "common.h"
#include "state-core.h"
#include "state-sdl.h"
#include <SDL2/SDL_render.h>
#include <string_view>

class Renderer {

	public:
	void Initialize(const std::string_view& windowName);

	StateCore& GetStateCore() noexcept;

	StateSDL& GetStateSDL() noexcept;

	SDL_Renderer* GetRenderer() noexcept;

	void Dispose() noexcept;

	private:
	bool InitializeSDL(const std::string_view& windowName);
	StateCore m_stateCore{};
	StateSDL m_stateSDL = { .windowX = 1200, .windowY = 800, };

	SDL_Renderer* m_internalRenderer = nullptr;


};

static inline Renderer g_renderer{};
