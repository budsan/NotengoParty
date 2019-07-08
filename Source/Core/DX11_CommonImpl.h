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

struct System_DX11Impl
{
	HINSTANCE hInstance;
	int nCmdShow;
	MSG msg;
};

struct Window_DX11Impl
{
	WNDCLASSEX wc;
	HWND hWnd;
};

struct Renderer_DX11Impl
{
	RendererState current;
	ID3D11Device* pd3dDevice;
	ID3D11DeviceContext* pd3dDeviceContext;
	IDXGISwapChain* pSwapChain;
	ID3D11RenderTargetView* mainRenderTargetView;
};

struct Texture2D_DX11Impl
{

};

void IOThread_Init();
void IOThread_Destroy();

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

extern System_DX11Impl dx11SysInst;
