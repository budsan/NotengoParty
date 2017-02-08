#pragma once

#include "Core/Engine.h"

struct Game
{
	ImFontAtlas _fontAtlas;
	ImFont* _font;
	ImDrawList* _fontDrawList;
	float _fontSize;
	size_t _lastJoystickId;

	void Init(Engine* engine);
	void Update(Engine* engine);
	void Render(Engine* engine);
	void Quit(Engine* engine);
};