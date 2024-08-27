#pragma once

#include <SDL2/SDL_opengl.h>

struct TextureData {
	GLuint id;
	GLenum format;
	GLenum min_filter;
	GLenum mag_filter;
	uint16_t width;
	uint16_t height;
};
