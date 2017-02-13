#pragma once

#include "Renderer.h"
#include "Input.h"

#include "LightVector.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"

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

typedef GLuint Texture2D_SDLImpl;

void Input_SDL_Event_JoyDeviceAdded(SDL_Event* event);
void Input_SDL_Event_JoyDeviceRemoved(SDL_Event* event);
void Input_SDL_JoysticksUpdateState();
