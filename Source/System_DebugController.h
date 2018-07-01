#pragma once

#include "Core/Engine.h"
#include "Core/File.h"

#include "System.h"

struct System_DebugController : public System
{
	ImFontAtlas _fontAtlas;
	ImFont* _font;
	ImDrawList* _fontDrawList;
	float _fontSize;
	size_t _lastJoystickId;
	FileReadAsync _readAsync;
	bool _allLoaded;

	System_DebugController() : System(SystemPriority_DebugControler) {}

	ImDrawList* GetDrawList() { return _fontDrawList; }
	void Init(Engine* engine);
	void DoJob(Engine* engine);
	void Quit(Engine* engine);
};