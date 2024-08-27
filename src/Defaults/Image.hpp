#pragma once

/// @brief Gets an image from either a server request or a local path
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_render.h>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class Image {
	public:
	Image() = default;

	~Image();

	void Init(uint32_t width, uint32_t height);

	void FetchFromUrl(const std::string& uri);

	GLuint GetTexture();

	uint32_t Width() const noexcept;

	uint32_t Height() const noexcept;

	private:
	std::vector<uint8_t> data{};

	uint32_t m_width;
	uint32_t m_height;

	GLuint m_cachedTextureId = 0u;

};
