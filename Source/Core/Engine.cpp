#include "Engine.h"

#include <string.h>

enum EngineFlags
{
	EngineFlagRunning = (1 << 0)
};

void Engine_Init(Engine* engine, const char* name, int32_t w, int32_t h)
{
	memset(engine, 0, sizeof(Engine));

	System_Init(engine);
	Window_Create(engine, name, w, h);
	Renderer_Create(engine);
	Renderer_SetViewport((float) w, (float) h);

	engine->flags = 0;
	engine->flags |= EngineFlagRunning;
}

void Engine_Update(Engine* engine)
{
	System_Update(engine);
}

void Engine_Quit(Engine* engine)
{
	Renderer_Destroy(engine);
	Window_Destroy(engine);
	System_Quit(engine);
}

bool Engine_IsRunning(Engine* engine)
{
	return (engine->flags & EngineFlagRunning) > 0;
}

void Engine_Close(Engine* engine)
{
	engine->flags &= ~EngineFlagRunning;
}