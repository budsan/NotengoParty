#ifdef SDL_IMPL

#include "Engine.h"
#include "System.h"
#include "SDL_CommonImpl.h"

size_t debug_allocations = 0;

void System_Init(Engine* engine)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK);
}

void System_Update(Engine* engine)
{
	// Window events //
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		/*bool handled = ImGui_ImplSdl_ProcessEvent(&event);
		if (handled)
			continue;*/

		if (event.type == SDL_WINDOWEVENT)
		{
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_CLOSE:
			{
				Engine_Close(engine);
				//handled = true;
				break;
			} 
			}
		}
	}
}

void System_Quit(Engine* engine)
{
	SDL_Quit();

	SYS_ASSERT(debug_allocations == 0);
}

uint32_t System_Ticks()
{
	return SDL_GetTicks();
}

void System_Sleep(uint32_t ticks)
{
	SDL_Delay(ticks);
}

void* SysMalloc(size_t size)
{
	debug_allocations++;
	return malloc(size);
}

void SysFree(void* ptr)
{
	free(ptr);
	debug_allocations--;
}

#endif