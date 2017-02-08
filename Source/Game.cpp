#include "Game.h"
#include "Core/Input.h"
#include "Core/Texture.h"
#include "Core/imgui/imgui_impl_sdl.h"

static char _textBuffer[128];

void Game_ControllerAdded(void* inst, const ControllerInfo* info)
{
	Game* game = reinterpret_cast<Game*>(inst);
	game->_lastJoystickId = game->_lastJoystickId <= info->Id ? info->Id+1 : game->_lastJoystickId;

	/*sprintf_s(_textBuffer, sizeof(_textBuffer), "%s. id %d. b %d. a %d. tb %d", info->Name, info->Id, info->NumButtons, info->NumButtons, info->numAxes, info->NumTrackballs);
	reinterpret_cast<Game*>(inst)->_text = _textBuffer;
	reinterpret_cast<Game*>(inst)->_color = 0xFFFFFFFF;*/
}

void Game_ControllerRemoved(void* inst, const ControllerInfo* info)
{
	/*sprintf_s(_textBuffer, sizeof(_textBuffer), "%s", info->Name);
	reinterpret_cast<Game*>(inst)->_text = _textBuffer;
	reinterpret_cast<Game*>(inst)->_color = 0xFF0000FF;*/
}

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

	Input_ControllerCallbacks _controllerCallback =
	{
		this,
		Game_ControllerAdded,
		Game_ControllerRemoved,
	};

	Input_SetControllerCallbacks(_controllerCallback);
	_lastJoystickId = 0;
}

void Game::Update(Engine* engine)
{
	_fontDrawList->Clear();
	_fontDrawList->PushClipRectFullScreen();
	_fontDrawList->PushTextureID(_fontAtlas.TexID);

	for (size_t i = 0; i < _lastJoystickId; i++)
	{
		ImVec2 fontPos(20, i * (10 + _fontSize) +  20);
		const ControllerInfo* info = Input_GetControllerInfo(i);

		if (info != nullptr)
		{
			sprintf_s(_textBuffer, sizeof(_textBuffer), "%s. id %d. b %d. a %d. tb %d", info->Name, info->Id, info->NumButtons, info->NumButtons, info->numAxes, info->NumTrackballs);
			_fontDrawList->AddText(_font, _fontSize, fontPos, 0xFFFFFFFF, _textBuffer, NULL, 0);
		}
	}
	
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

	ImGuiIO& io = ImGui::GetIO();
	io.RenderDrawListsFn(&RenderDrawData);

	Renderer_Present(engine);
}

void Game::Quit(Engine* engine)
{
	SysFree(_fontDrawList);
}



