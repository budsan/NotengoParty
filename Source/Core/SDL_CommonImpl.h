#pragma once

#include "Renderer.h"

#include "LightVector.h"

#include <SDL.h>
//#include "imgui_impl_sdl.h"

struct Window_SDLImpl
{
	SDL_Window* sdl_window;
	LightVector<char> res_string_buffer;
	LightVector<const char*> res_string_array;
};

struct Renderer_SDLImpl
{
	SDL_GLContext context;
	RendererState current;
};