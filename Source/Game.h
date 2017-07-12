#pragma once

#include "Core/Engine.h"
#include "Core/File.h"

struct Game
{
	ImFontAtlas _fontAtlas;
	ImFont* _font;
	ImDrawList* _fontDrawList;
	float _fontSize;
	size_t _lastJoystickId;
	FileReadAsync _readAsync;
	bool _allLoaded;

	void Init(Engine* engine);
	void Update(Engine* engine);
	void Render(Engine* engine);
	void Quit(Engine* engine);
};