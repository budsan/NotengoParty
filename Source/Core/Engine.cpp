#include "Engine.h"

#include <string.h>

enum EngineFlags
{
	EngineFlagRunning = (1 << 0)
};

void Engine::Init(const char* name, int32_t w, int32_t h)
{
	memset(this, 0, sizeof(Engine));

	System_Init(this);
	Window_Create(this, name, w, h);
	Renderer_Create(this);
	Renderer_SetViewport((float) w, (float) h);

	flags = 0;
	flags |= EngineFlagRunning;
}

void Engine::Update()
{
	System_Update(this);
}

void Engine::Quit()
{
	Renderer_Destroy(this);
	Window_Destroy(this);
	System_Quit(this);
}

bool Engine::IsRunning()
{
	return (flags & EngineFlagRunning) > 0;
}

void Engine::Close()
{
	flags &= ~EngineFlagRunning;
}