#include "Game.h"
#include "Core/Texture.h"

void Game::Init(Engine* engine)
{
	_fontSize = 32;
	_fontDrawList = (ImDrawList*)SysMalloc(sizeof(ImDrawList));
	SYS_PLACEMENT_NEW(_fontDrawList) ImDrawList();
	_font = _fontAtlas.AddFontFromFileTTF("Data/Fonts/ArvinLight.ttf", _fontSize);

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
	const char testText[] = "Test";
	const char* testTextEnd = testText + sizeof(testText);

	ImVec2 fontPos(0, 0);
	_fontDrawList->Clear();
	_fontDrawList->PushClipRectFullScreen();
	_fontDrawList->PushTextureID(_fontAtlas.TexID);
	_fontDrawList->AddText(_font, _fontSize, fontPos, 0xFFFFFFFF, testText, testTextEnd);

	Renderer_ImGui_NewFrame(engine);

	const ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoSavedSettings
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoCollapse;

	bool menuOpen = true;
	ImGui::SetNextWindowPosCenter();
	ImGui::SetNextWindowSize(ImVec2(600, 600));
	ImGui::Begin("Test", &menuOpen, windowFlags);
	ImGui::LabelText("TestLabel", "");
	ImGui::End();
}

void Game::Render(Engine* engine)
{
	Renderer_Clear(engine, 0, 0, 0, 255);
	ImGui::Render();
	Renderer_Present(engine);
}

void Game::Quit(Engine* engine)
{
	SysFree(_fontDrawList);
}



