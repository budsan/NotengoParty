#pragma once

#include "Core/Engine.h"
#include "System.h"

#define MAX_NUM_SYSTEMS 128

struct System_Manager
{
	size_t _systems_now;
	size_t _systems_added;
	System* _systems[MAX_NUM_SYSTEMS];

	void Init(Engine* engine);
	void Quit(Engine* engine);

	void AddSystem(System* system);
	void DoJob(Engine* engine);
};