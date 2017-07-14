#include "Game.h"
#include "Core/Input.h"
#include "Core/Texture.h"
#include "Core/imgui/imgui_impl_sdl.h"

static char _textBuffer[128];

const char* HatStateName[] =
{
		"CENTERED",
		"RIGHT",
		"LEFT",
		"0011 CENTERED",
		"UP",
		"RIGHTUP",
		"LEFTUP",
		"0111 UP",
		"DOWN",
		"RIGHTDOWN",
		"LEFTDOWN",
		"1011 DOWN",
		"1100 CENTERED",
		"1101 LEFT",
		"1110 RIGHT",
		"1111 CENTERED"
};

inline ControllerState::HatType AxisToHat(ControllerState::AxisType x, ControllerState::AxisType y)
{
	const ControllerState::AxisType threshold = 1 << (sizeof(ControllerState::AxisType) * 7);

	ControllerState::HatType mask = 0;
	mask |= (x >  threshold) ? 1 << 0 : 0;
	mask |= (x < -threshold) ? 1 << 1 : 0;
	mask |= (y < -threshold) ? 1 << 2 : 0;
	mask |= (y >  threshold) ? 1 << 3 : 0;

	return mask;
}

inline ControllerState::HatType AxisToHat(const ControllerState* state)
{
	return AxisToHat(state->AxisState[0], state->AxisState[1]);
}

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

const char *int_to_binary(uint32_t x)
{
	static char b[33];
	uint32_t i;
	for (i = 0; i < 32; i++)
		b[i] = (x & (1 << i)) ? '1' : '0';

	b[32] = '\0';
	return b;
}

const char* FindRenderedTextEnd(const char* text, const char* text_end)
{
	const char* text_display_end = text;
	if (!text_end)
		text_end = (const char*)-1;

	while (text_display_end < text_end && *text_display_end != '\0' && (text_display_end[0] != '#' || text_display_end[1] != '#'))
		text_display_end++;
	return text_display_end;
}

ImVec2 CalcTextSize(ImFont* font, float font_size, const char* text, const char* text_end, bool hide_text_after_double_hash, float wrap_width)
{
	const char* text_display_end;
	if (hide_text_after_double_hash)
		text_display_end = FindRenderedTextEnd(text, text_end);      // Hide anything after a '##' string
	else
		text_display_end = text_end;

	if (text == text_display_end)
		return ImVec2(0.0f, font_size);
	ImVec2 text_size = font->CalcTextSizeA(font_size, FLT_MAX, wrap_width, text, text_display_end, NULL);

	// Cancel out character spacing for the last character of a line (it is baked into glyph->XAdvance field)
	const float font_scale = font_size / font->FontSize;
	const float character_spacing_x = 1.0f * font_scale;
	if (text_size.x > 0.0f)
		text_size.x -= character_spacing_x;
	text_size.x = (float)(int)(text_size.x + 0.95f);

	return text_size;
}

//---------------------------------------------------------------------------//

void Game::Init(Engine* engine)
{
	ImGuiIO& io = ImGui::GetIO();

	_fontSize = 32;
	_fontDrawList = (ImDrawList*)SysMalloc(sizeof(ImDrawList));
	SYS_PLACEMENT_NEW(_fontDrawList) ImDrawList();

	File_LoadToMemoryAsync("Data/Fonts/ArvinRegular.ttf", &_readAsync);
	_allLoaded = false;

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
	if (_allLoaded)
	{
		_fontDrawList->Clear();
		_fontDrawList->PushClipRectFullScreen();

		for (size_t i = 0; i < _lastJoystickId; i++)
		{
			ImVec2 fontPos(20, i * 3 * (10 + _fontSize) + 20);
			const ControllerInfo* info = Input_GetControllerInfo(i);
			const ControllerState* state = Input_GetControllerState(i);

			if (info != nullptr)
			{
				sprintf_s(_textBuffer, sizeof(_textBuffer), "%s. id %d. b %d. a %d.\n%s\n%s",
					info->Name,
					info->Id,
					info->NumButtons,
					info->numAxes,
					int_to_binary(state->ButtonMaskState),
					HatStateName[state->HatState | AxisToHat(state)]);

				ImVec2 textSize = CalcTextSize(_font, _fontSize, _textBuffer, NULL, false, 0);
				ImVec2 fontPos2(fontPos.x + textSize.x, fontPos.y + textSize.y);
				
				_fontDrawList->AddRectFilled(fontPos, fontPos2, 0xFFFFFFFF);
				_fontDrawList->PushTextureID(_fontAtlas.TexID);
				_fontDrawList->AddText(_font, _fontSize, fontPos, 0xFF333333, _textBuffer, NULL, 0);
				_fontDrawList->PopTextureID();
			}
		}

		Renderer_ImGui_NewFrame(engine);
	}
	else
	{
		if (_readAsync.completed)
		{
			_font = _fontAtlas.AddFontFromMemoryTTF(_readAsync.data, _readAsync.size, _fontSize);

			SYS_DEBUG_DECR_ALLOC;
			_readAsync.data = NULL;
			_readAsync.size = 0;
			
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

			_allLoaded = true;
		}
	}
}

void Game::Render(Engine* engine)
{
	Renderer_Clear(engine, 0, 0, 0, 255);

	if (_allLoaded)
	{
		ImDrawData RenderDrawData;
		RenderDrawData.CmdLists = &_fontDrawList;
		RenderDrawData.CmdListsCount = _fontDrawList->VtxBuffer.size() > 0 ? 1 : 0;
		RenderDrawData.TotalVtxCount = _fontDrawList->VtxBuffer.size();
		RenderDrawData.TotalIdxCount = _fontDrawList->IdxBuffer.size();

		ImGuiIO& io = ImGui::GetIO();
		io.RenderDrawListsFn(&RenderDrawData);
	}

	Renderer_Present(engine);
}

void Game::Quit(Engine* engine)
{
	Texture2D_Destroy(engine, _fontAtlas.TexID);
	SysFree(_fontDrawList);
}



