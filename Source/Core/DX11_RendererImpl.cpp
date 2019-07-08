#ifdef DX11_IMPL

#include "Engine.h"
#include "Renderer.h"
#include <math.h>

#include "DX11_CommonImpl.h"

void Renderer_CreateRenderTarget(Renderer_DX11Impl* renderer)
{
	ID3D11Texture2D* pBackBuffer;
	renderer->pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);
	renderer->pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &renderer->mainRenderTargetView);
	pBackBuffer->Release();
}

void Renderer_CleanupRenderTarget(Renderer_DX11Impl* renderer)
{
	if (renderer->mainRenderTargetView)
	{ 
		renderer->mainRenderTargetView->Release();
		renderer->mainRenderTargetView = NULL;
	}
}

void Renderer_ImGui_NewFrame(Engine* engine)
{
}

void Renderer_Create(Engine* engine)
{
	Window_DX11Impl* window = (Window_DX11Impl*)engine->window;
	Renderer_DX11Impl* renderer = (Renderer_DX11Impl*)SysMalloc(sizeof(Renderer_DX11Impl));
	engine->renderer = renderer;

	// Setup swap chain
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = window->hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT createDeviceFlags = 0;
	//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &renderer->pSwapChain, &renderer->pd3dDevice, &featureLevel, &renderer->pd3dDeviceContext) != S_OK)
	{
		SYS_LOG("Error D3D11CreateDeviceAndSwapChain");
		Renderer_Destroy(engine);
		return;
	}

	ShowWindow(window->hWnd, dx11SysInst.nCmdShow);
	UpdateWindow(window->hWnd);
}

void Renderer_Destroy(Engine* engine)
{
	Renderer_DX11Impl* renderer = (Renderer_DX11Impl*)engine->renderer;
	Renderer_CleanupRenderTarget(renderer);
	if (renderer->pSwapChain) { renderer->pSwapChain->Release(); renderer->pSwapChain = NULL; }
	if (renderer->pd3dDeviceContext) { renderer->pd3dDeviceContext->Release(); renderer->pd3dDeviceContext = NULL; }
	if (renderer->pd3dDevice) { renderer->pd3dDevice->Release(); renderer->pd3dDevice = NULL; }

	SysFree(renderer);
	engine->renderer = NULL;
}

void Renderer_Clear(Engine* engine, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	float clear_color[4] = { r / 255.0f, g / 255.f, b /255.f, a / 255.f };
	Renderer_DX11Impl* renderer = (Renderer_DX11Impl*)engine->renderer;
	renderer->pd3dDeviceContext->OMSetRenderTargets(1, &renderer->mainRenderTargetView, NULL);
	renderer->pd3dDeviceContext->ClearRenderTargetView(renderer->mainRenderTargetView, clear_color);
}

void Renderer_SetViewport(float TopLeftX, float TopLeftY, float width, float height)
{
}

void Renderer_DrawLogic(Engine* engine, DrawList* drawlist)
{
}

void Renderer_Present(Engine* engine)
{
	Renderer_DX11Impl* renderer = (Renderer_DX11Impl*)engine->renderer;
	renderer->pSwapChain->Present(1, 0); // Present with vsync
	//renderer->pSwapChain->Present(0, 0); // Present without vsync
}

#endif