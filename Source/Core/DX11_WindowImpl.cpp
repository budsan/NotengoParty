#if DX11_IMPL

#include <string.h>

#include "Engine.h"
#include "Window.h"
#include "DX11_CommonImpl.h"

#include <windows.h>
#include <windowsx.h>

//-----------------------------------------------------------------------------

void Window_Create(Engine* engine, const char* name, int w, int h)
{
	SYS_ASSERT(engine->window == NULL);

	Window_DX11Impl* window = (Window_DX11Impl*)SysMalloc(sizeof(Window_DX11Impl));
	window->wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WindowProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, name, NULL };
	RegisterClassEx(&window->wc);

	window->hWnd = CreateWindow(name, name, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, w, h, NULL, NULL, dx11SysInst.hInstance, NULL);
	engine->window = window;
}

void Window_Destroy(Engine* engine)
{

}

void Window_SetTitle(Engine* engine, const char* title)
{

}

void Window_GetSize(Engine* engine, int* width, int* height)
{

}

const char** Window_GetResolutions(Engine* engine, int* res_count, int* current)
{
	return nullptr;
}

void Window_SetResolution(Engine* engine, const char* resolution)
{

}

const char** Window_GetModes(Engine* engine, int* modes_count, int* current)
{
	return nullptr;
}

void Window_SetMode(Engine* engine, const char* mode)
{

}

#endif