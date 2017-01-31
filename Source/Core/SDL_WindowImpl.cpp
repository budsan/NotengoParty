#if SDL_IMPL

#include <string.h>

#include "Engine.h"
#include "Window.h"
#include "SDL_CommonImpl.h"

const char* SDLModes[] =
{
	"Windowed",
	"Borderless Window",
	"Fullscreen"
};

enum WindowMode
{
	ModeWindowed = 0,
	ModeBorderlessWindow = 1,
	ModeFullscreen = 2,
	ModeCount = 3
};

void Window_Create(Engine* engine, const char* name, int w, int h)
{
	SYS_ASSERT(engine->window == NULL);

	Window_SDLImpl* window = (Window_SDLImpl*)SysMalloc(sizeof(Window_SDLImpl));
	SYS_PLACEMENT_NEW(&window->res_string_buffer) LightVector<char>();
	SYS_PLACEMENT_NEW(&window->res_string_array) LightVector<char>();

	window->sdl_window = SDL_CreateWindow(
		name,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		w, h,
		SDL_WINDOW_OPENGL /*| SDL_WINDOW_FULLSCREEN*/
	);

	if (window->sdl_window == NULL)
	{
		SYS_LOG("Could not create window: %s\n", SDL_GetError());
	}

	engine->window = window;
}

void Window_Destroy(Engine* engine)
{
	SYS_ASSERT(engine->window != NULL);
	Window_SDLImpl* window = (Window_SDLImpl*)engine->window;
	SDL_DestroyWindow(window->sdl_window);
	SysFree(window);
	engine->window = NULL;
}

void Window_SetTitle(Engine* engine, const char* title)
{
	SYS_ASSERT(engine->window != NULL);
	Window_SDLImpl* window = (Window_SDLImpl*)engine->window;
	SDL_SetWindowTitle(window->sdl_window, title);
}

void Window_GetSize(Engine* engine, int* width, int* height)
{
	SYS_ASSERT(engine->window != NULL);
	Window_SDLImpl* window = (Window_SDLImpl*)engine->window;
	SDL_Window* sdl_window = window->sdl_window;
	Uint32 flags = SDL_GetWindowFlags(sdl_window);
	if (flags & SDL_WINDOW_FULLSCREEN)
	{
		SDL_DisplayMode mode;
		SDL_GetCurrentDisplayMode(0, &mode);
		*width = mode.w;
		*height = mode.h;
	}
	else
	{
		SDL_GetWindowSize(window->sdl_window, width, height);
	}
}

const char** Window_GetResolutions(Engine* engine, int* res_count, int* current)
{
	SYS_ASSERT(engine->window != NULL);
	Window_SDLImpl* window = (Window_SDLImpl*)engine->window;
	SDL_Window* sdl_window = window->sdl_window;
	Uint32 flags = SDL_GetWindowFlags(sdl_window);

	static char buffer[64];
	if (window->res_string_array.empty())
	{
		int displayIndex = 0;
		//int numDisplay = SDL_GetNumVideoDisplays();
		//for (int displayIndex = 0; displayIndex < numDisplay; displayIndex++)
		{
			int numModesInserted = 0;
			int numModes = SDL_GetNumDisplayModes(displayIndex);
			for (int modeIndex = 0; modeIndex < numModes; ++modeIndex)
			{
				SDL_DisplayMode mode;
				SDL_GetDisplayMode(0, modeIndex, &mode);
				sprintf(buffer, "%dx%d", mode.w, mode.h);

				int i = 0;
				char* iter = window->res_string_buffer.begin();
				for (; i < numModesInserted; i++)
				{
					if (strcmp(buffer, iter) == 0)
						break;

					iter += strlen(iter) + 1;
				}

				if (i == numModesInserted)
				{
					int len = strlen(buffer);
					int curr_size = window->res_string_buffer.size();
					window->res_string_buffer.resize(curr_size + len + 1);
					char* begin = &window->res_string_buffer[curr_size];
					strcpy(begin, buffer);
					numModesInserted++;
				}
			}

			window->res_string_array.reserve(numModesInserted);
			char* iter = window->res_string_buffer.begin();
			for (int i = 0; i < numModesInserted; i++)
			{
				window->res_string_array.push_back(iter);
				iter += strlen(iter) + 1;
			}
		}
	}

	SDL_DisplayMode mode { SDL_PIXELFORMAT_RGBA8888, 0, 0, 60, NULL };
	if (flags & SDL_WINDOW_FULLSCREEN)
	{
		SDL_GetCurrentDisplayMode(0, &mode);
	}
	else
	{
		int width, height;
		SDL_GetWindowSize(sdl_window, &width, &height);
		SDL_DisplayMode desired = { SDL_PIXELFORMAT_RGBA8888, width, height, 60, NULL };
		SDL_DisplayMode* ptr = SDL_GetClosestDisplayMode(0, &desired, &mode);
	}

	sprintf(buffer, "%dx%d", mode.w, mode.h);
	int i = 0;
	for (; i < window->res_string_array.size(); i++)
	{
		if (strcmp(buffer, window->res_string_array[i]) == 0)
		{
			break;
		}
	}

	*current = (i == window->res_string_array.size()) ? 0 : i;
	*res_count = window->res_string_array.size();
	return &window->res_string_array.front();
}

void Window_SetResolution(Engine* engine, const char* resolution)
{
	SYS_ASSERT(engine->window != NULL);
	Window_SDLImpl* window = (Window_SDLImpl*)engine->window;
	SDL_Window* sdl_window = window->sdl_window;
	Uint32 flags = SDL_GetWindowFlags(sdl_window);

	int width, height;
	sscanf(resolution, "%dx%d", &width, &height);
	if (flags & SDL_WINDOW_FULLSCREEN)
	{
		SDL_DisplayMode closest;
		SDL_DisplayMode mode{ SDL_PIXELFORMAT_RGBA8888, width, height, 60, NULL };
		SDL_DisplayMode* ptr = SDL_GetClosestDisplayMode(0, &mode, &closest);
		if (ptr != NULL)
		{
			int result = SDL_SetWindowDisplayMode(sdl_window, &closest);
			SYS_LOG("%s fullscreen resolution to %dx%d.\n", result == 0 ? "Changed" : "Failed to change", ptr->w, ptr->h);
		}
	}
	else
	{
		SDL_SetWindowSize(sdl_window, width, height);
		SDL_SetWindowPosition(sdl_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
}

const char** Window_GetModes(Engine* engine, int* modes_count, int* current)
{
	SYS_ASSERT(engine->window != NULL);
	Window_SDLImpl* window = (Window_SDLImpl*)engine->window;
	SDL_Window* sdl_window = window->sdl_window;
	Uint32 flags = SDL_GetWindowFlags(sdl_window);
	if (flags & SDL_WINDOW_FULLSCREEN)
	{
		*current = ModeFullscreen;
	}
	else
	{
		if (flags & SDL_WINDOW_BORDERLESS)
		{
			*current = ModeBorderlessWindow;
		}
		else
		{
			*current = ModeWindowed;
		}
	}

	*modes_count = ModeCount;
	return SDLModes;
}

void Window_SetMode(Engine* engine, const char* mode)
{
	SYS_ASSERT(engine->window != NULL);
	SYS_ASSERT(mode != NULL);

	Window_SDLImpl* window = (Window_SDLImpl*)engine->window;
	SDL_Window* sdl_window = window->sdl_window;
	Uint32 flags = SDL_GetWindowFlags(sdl_window);
	uint32_t targetmode;
	for (targetmode = 0; targetmode < ModeCount; targetmode++)
	{
		if (strcmp(mode, SDLModes[targetmode]) == 0)
		{
			break;
		}
	}
	
	if (targetmode == ModeFullscreen)
	{
		if ((flags & SDL_WINDOW_FULLSCREEN) == 0)
		{
			SDL_SetWindowFullscreen(sdl_window, SDL_WINDOW_FULLSCREEN);
		}
	}
	else
	{
		if ((flags & SDL_WINDOW_FULLSCREEN) != 0)
		{
			SDL_SetWindowFullscreen(sdl_window, 0);
		}

		if ((flags & SDL_WINDOW_BORDERLESS) != 0 && targetmode == ModeWindowed)
		{
			SDL_SetWindowBordered(sdl_window, SDL_TRUE);
		}
		else if ((flags & SDL_WINDOW_BORDERLESS) == 0 && targetmode == ModeBorderlessWindow)
		{
			SDL_SetWindowBordered(sdl_window, SDL_FALSE);
		}
	}
}

#endif