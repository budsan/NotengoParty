#pragma once

#include "Core/Engine.h"

struct Game
{
	ImFontAtlas _fontAtlas;
	ImFont* _font;
	ImDrawList* _fontDrawList;

	Input_ControllerCallbacks _controllerCallback;
	const char* _text;
	uint32_t _color;

	float _fontSize;

	void Init(Engine* engine);
	void Update(Engine* engine);
	void Render(Engine* engine);
	void Quit(Engine* engine);
};