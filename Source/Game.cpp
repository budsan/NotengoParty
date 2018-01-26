#include "Game.h"
#include "InputAux.h"
#include "UI.h"

#include "Core/Input.h"
#include "Core/Texture.h"
#include "Core/imgui/imgui_impl_sdl.h"


void Game::Init(Engine* engine)
{
	_debugController.Init(engine);
	_gameDrawList = (ImDrawList*)SysMalloc(sizeof(ImDrawList));
	SYS_PLACEMENT_NEW(_gameDrawList) ImDrawList();
}

void Game::Update(Engine* engine)
{
	_debugController.Update(engine);

	_gameDrawList->Clear();
	_gameDrawList->PushClipRectFullScreen();
	_gameDrawList->AddRectFilled(ImVec2(100, 100), ImVec2(100, 100), 0xFFFFFFFF);

	Renderer_ImGui_NewFrame(engine);
}

void Game::Render(Engine* engine)
{
	Renderer_Clear(engine, 0, 0, 0, 255);

	ImDrawList* debugControllerDrawList = _debugController.GetDrawList();

	int CmdListsCount = 0;
	if (debugControllerDrawList->VtxBuffer.size() > 0)
		_cmdLists[CmdListsCount++] = debugControllerDrawList;
	if (_gameDrawList->VtxBuffer.size() > 0)
		_cmdLists[CmdListsCount++] = _gameDrawList;

	ImDrawData RenderDrawData;
	RenderDrawData.CmdLists = _cmdLists;

	RenderDrawData.CmdListsCount = CmdListsCount;
	RenderDrawData.TotalVtxCount = 0;
	RenderDrawData.TotalIdxCount = 0;

	for (size_t i = 0; i < CmdListsCount; i++)
	{
		RenderDrawData.TotalVtxCount += _cmdLists[i]->VtxBuffer.size();
		RenderDrawData.TotalIdxCount += _cmdLists[i]->IdxBuffer.size();
	}

	ImGuiIO& io = ImGui::GetIO();
	io.RenderDrawListsFn(&RenderDrawData);

	Renderer_Present(engine);
}

void Game::Quit(Engine* engine)
{
	_debugController.Quit(engine);
	SysFree(_gameDrawList);
}



