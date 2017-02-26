#ifdef SDL_IMPL

#include "Engine.h"
#include "Texture.h"

#include "SDL_CommonImpl.h"

TextureType Texture2D_Create(Engine* engine, Texture2D_Description* desc, void* pixels)
{
	Texture2D_SDLImpl tex2d;

	GLint last_texture;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);

	glGenTextures(1, &tex2d);
	glBindTexture(GL_TEXTURE_2D, tex2d);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, desc->width, desc->height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, pixels);

	// Restore state
	glBindTexture(GL_TEXTURE_2D, last_texture);

	return reinterpret_cast<TextureType>((intptr_t)tex2d);
}

void Texture2D_Destroy(Engine* engine, TextureType texture)
{
	glDeleteTextures(1, (const GLuint*) &texture);
}


#endif