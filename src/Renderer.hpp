#pragma once

#include "state-core.h"
#include "state-sdl.h"
#include <string_view>

class Renderer {

	public:

	void Initialize(const std::string_view& windowName);

	StateCore& GetStateCore() noexcept;

	StateSDL& GetStateSDL() noexcept;

	void Dispose() noexcept;

	private:
	bool InitializeSDL(const std::string_view& windowName);
	StateCore m_stateCore{};
	StateSDL m_stateSDL = { .windowX = 1200, .windowY = 800, };


};
