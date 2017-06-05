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
	Input_SDL_JoysticksResetState();

	// Window events //
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		bool handled = ImGui_ImplSdl_ProcessEvent(&event);
		if (handled)
			continue;

		switch (event.type)
		{
		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_CLOSE:
				engine->Close();
				handled = true;
				break;
			}
			break;
		case SDL_JOYDEVICEADDED:
			Input_SDL_Event_JoyDeviceAdded(&event);
			break;
		case SDL_JOYDEVICEREMOVED:
			Input_SDL_Event_JoyDeviceRemoved(&event);
			break;
		case SDL_JOYBUTTONDOWN:
			Input_SDL_Event_JoyButtonDown(&event);
			break;
		case SDL_JOYBUTTONUP:
			Input_SDL_Event_JoyButtonUp(&event);
			break;
		case SDL_JOYHATMOTION:
			Input_SDL_Event_JoyHatMotion(&event);
			break;
		case SDL_JOYAXISMOTION:
			Input_SDL_Event_JoyAxisMotion(&event);
			break;
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

const char* System_GetClipboardText()
{
	return SDL_GetClipboardText();
}

bool System_SetClipboardText(const char *text)
{
	return SDL_SetClipboardText(text) < 0 ? false : true;
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