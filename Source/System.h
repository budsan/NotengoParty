#pragma once

#include "Core/Engine.h"

enum SystemPriority
{
	SystemPriority_First = 0,
	SystemPriority_DebugControler,
	SystemPriority_Last = 0xFFFF
};

enum SystemFlags
{
	SystemFlags_None = 0,
	SystemFlags_InitMe = (1 << 0),
	SystemFlags_RemoveMe = (1 << 1),
	SystemFlags_Disabled = (1 << 2)
};

struct System
{
	uint16_t priority;
	uint16_t flags;

	System(uint16_t _priority) : priority(_priority), flags(SystemFlags_None) {}

	virtual void Init(Engine* engine) = 0;
	virtual void DoJob(Engine* engine) = 0;
	virtual void Quit(Engine* engine) = 0;
};