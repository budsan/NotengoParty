#pragma once

#include "Renderer.h"
#include "Input.h"

#include "LightVector.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include <d3d11.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include "imgui/imgui.h"

struct Window_DX11Impl
{
};

struct Renderer_DX11Impl
{
	RendererState current;
};

struct Texture2D_SDLImpl
{

};

void IOThread_Init();
void IOThread_Destroy();
