#include <SDL2/SDL_error.h>
#include <SDL2/SDL_opengl.h>
#include <_types/_uint8_t.h>
#include <fstream>
#include <string>
#include "Image.hpp"
#include "Renderer.hpp"
#include "Utils/Parsing/lodepng.h"
#include "cpr/api.h"
#include "cpr/cprtypes.h"
#include "cpr/file.h"
#include "cpr/response.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rwops.h>
#include <SDL2/SDL_surface.h>
#include <cassert>
#include <cpr/cpr.h>
#include <cstddef>
#include <cstdio>
#include <exception>
#include <vector>


constexpr uint32_t RED_MASK = 0x000000FF;
constexpr uint32_t GREEN_MASK = 0x0000FF00;
constexpr uint32_t BLUE_MASK = 0x00FF0000;
constexpr uint32_t ALPHA_MASK = 0xFF000000;

void Image::Init(uint32_t width, uint32_t height) {
	this->data.reserve(width * height);
	this->m_width = width;
	this->m_height = height;
}

Image::~Image() {
	if (this->m_cachedTextureId == 0) return;
	glDeleteTextures(1, &this->m_cachedTextureId);
}

void Image::FetchFromUrl(const std::string& uri) {
	cpr::Url urlToUse(uri);
	cpr::Response res = cpr::Get(urlToUse);
	std::vector<uint8_t> rawPngData(res.text.begin(), res.text.end());
	lodepng::decode(this->data, this->m_width, this->m_height, rawPngData);
	(void)0;
}

GLuint Image::GetTexture() {
	if (this->m_cachedTextureId != 0u) {
		return this->m_cachedTextureId;
	}
	GLuint imageTexture;
	glGenTextures(1, &imageTexture);
	glBindTexture(GL_TEXTURE_2D, imageTexture);

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Optional
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Optional

	// Ensure the data is tightly packed
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Upload pixels into texture
	glTexImage2D(
	    GL_TEXTURE_2D,
	    0,
	    GL_RGBA,
	    this->m_width,
	    this->m_height,
	    0,
	    GL_RGBA,
	    GL_UNSIGNED_BYTE,
	    this->data.data()
	);

	// Check for OpenGL errors
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
	    fprintf(stderr, "OpenGL error: %d\n", err);
	}


	return this->m_cachedTextureId;
}

uint32_t Image::Width() const noexcept {
	return this->m_width;
}

uint32_t Image::Height() const noexcept {
	return this->m_height;
}
