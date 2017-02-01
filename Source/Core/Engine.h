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

	void Init(const char* name, int32_t w, int32_t h);
	void Update();
	void Quit();

	bool IsRunning();
	void Close();
};

