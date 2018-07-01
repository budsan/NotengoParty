#include "System_DebugController.h"
#include "InputAux.h"
#include "UI.h"

#include "Core/Input.h"
#include "Core/Texture.h"
#include "Core/imgui/imgui_impl_sdl.h"

static char _textBuffer[128];

void Game_ControllerAdded(void* inst, const ControllerInfo* info)
{
	System_DebugController* debugController = reinterpret_cast<System_DebugController*>(inst);
	debugController->_lastJoystickId = debugController->_lastJoystickId <= info->Id ? info->Id + 1 : debugController->_lastJoystickId;

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

//---------------------------------------------------------------------------//

void System_DebugController::Init(Engine* engine)
{
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

void System_DebugController::DoJob(Engine* engine)
{
	_fontDrawList->Clear();

	if (_allLoaded)
	{
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
					Input::GetHatStateName(state->HatState | Input::AxisToHat(state)));

				ImVec2 textSize = UI::CalcTextSize(_font, _fontSize, _textBuffer, NULL, false, 0);
				ImVec2 fontPos2(fontPos.x + textSize.x, fontPos.y + textSize.y);

				_fontDrawList->AddRectFilled(fontPos, fontPos2, 0xFFFFFFFF);
				_fontDrawList->PushTextureID(_fontAtlas.TexID);
				_fontDrawList->AddText(_font, _fontSize, fontPos, 0xFF333333, _textBuffer, NULL, 0);
				_fontDrawList->PopTextureID();
			}
		}
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

void System_DebugController::Quit(Engine* engine)
{
	Texture2D_Destroy(engine, _fontAtlas.TexID);
	SysFree(_fontDrawList);
}



