#pragma once

#include <stdint.h>

struct Engine;
typedef void* TextureType;

enum TextureFormat
{
	TextureFormatA8,

	// Add more formats on demand
};

struct Texture2D_Description
{
	uint16_t width;
	uint16_t height;
	uint8_t format;

	// Only 1 base texture, no mipmap for now
	//uint8_t miplevels;
	//uint8_t arraysize;
};

TextureType Texture2D_Create(Engine* engine, Texture2D_Description* desc, void* pixels);