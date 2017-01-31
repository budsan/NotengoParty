#pragma once

#include <stdint.h>

#include "System.h"
#include "Window.h"
#include "Renderer.h"
#include "Input.h"

struct Engine
{
	WindowType window;
	RendererType renderer;
	uint32_t flags;
	uint32_t delta_time;
	uint32_t running_time;
};

void Engine_Init(Engine* engine, const char* name, int32_t w, int32_t h);
void Engine_Update(Engine* engine);
void Engine_Quit(Engine* engine);

bool Engine_IsRunning(Engine* engine);
void Engine_Close(Engine* engine);
