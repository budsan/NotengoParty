#pragma once

#include "Core/Engine.h"
#include "Core/File.h"

struct DebugController
{
	ImFontAtlas _fontAtlas;
	ImFont* _font;
	ImDrawList* _fontDrawList;
	float _fontSize;
	size_t _lastJoystickId;
	FileReadAsync _readAsync;
	bool _allLoaded;

	ImDrawList* GetDrawList() { return _fontDrawList; }
	void Init(Engine* engine);
	void Update(Engine* engine);
	void Quit(Engine* engine);
};