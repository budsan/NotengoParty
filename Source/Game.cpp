#include "Game.h"
#include "Core/Texture.h"
#include "Core/imgui/imgui_impl_sdl.h"

void Game::Init(Engine* engine)
{
	_fontSize = 32;
	_fontDrawList = (ImDrawList*)SysMalloc(sizeof(ImDrawList));
	SYS_PLACEMENT_NEW(_fontDrawList) ImDrawList();
	_font = _fontAtlas.AddFontFromFileTTF("Data/Fonts/ArvinRegular.ttf", _fontSize);

	unsigned char* pixels;
	int width, height;
	_fontAtlas.GetTexDataAsAlpha8(&pixels, &width, &height);
	{
		Texture2D_Description desc;
		desc.width = width;
		desc.height = height;
		desc.format = TextureFormatA8;

		_fontAtlas.TexID = Texture2D_Create(engine, &desc, pixels);
	}
}

void Game::Update(Engine* engine)
{
	const char testText[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus sed diam dui. Vivamus ultrices iaculis elit, non varius orci auctor.";
	const char* testTextEnd = testText + sizeof(testText) - 1;

	ImVec2 fontPos(20, 20);
	_fontDrawList->Clear();
	_fontDrawList->PushClipRectFullScreen();
	_fontDrawList->PushTextureID(_fontAtlas.TexID);
	_fontDrawList->AddText(_font, _fontSize, fontPos, 0xFFFFFFFF, testText, testTextEnd, 400);

	Renderer_ImGui_NewFrame(engine);
}

void Game::Render(Engine* engine)
{
	Renderer_Clear(engine, 0, 0, 0, 255);

	ImDrawData RenderDrawData;
	RenderDrawData.CmdLists = &_fontDrawList;
	RenderDrawData.CmdListsCount = 1;
	RenderDrawData.TotalVtxCount = _fontDrawList->VtxBuffer.Size;
	RenderDrawData.TotalIdxCount = _fontDrawList->IdxBuffer.Size;

	ImGui_ImplSdl_RenderDrawLists(&RenderDrawData);

	Renderer_Present(engine);
}

void Game::Quit(Engine* engine)
{
	SysFree(_fontDrawList);
}



