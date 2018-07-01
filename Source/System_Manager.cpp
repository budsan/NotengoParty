#include "System_Manager.h"

uint16_t get_system_priority_safe(System* sys)
{
	return sys != NULL ? sys->priority : SystemPriority_Last;
}

void sort_systems(System** _systems, size_t size)
{
	for (size_t i = 1; i < size; i++)
	{
		System* aux = _systems[i];
		size_t j = i - 1;
		while (get_system_priority_safe(aux) < get_system_priority_safe(_systems[j]) && j >= 0)
		{
			_systems[j + 1] = _systems[j];
			j--;
		}
		_systems[j + 1] = aux;
	}
}

//---------------------------------------------------------------------- member functions

void System_Manager::Init(Engine* engine)
{
	for (size_t i = 0; i < MAX_NUM_SYSTEMS; i++)
	{
		_systems[i] = NULL;
	}

	_systems_now = 0;
	_systems_added = 0;
}

void System_Manager::Quit(Engine* engine)
{
	for (size_t i = 1; i < _systems_now; i++)
	{
		System* sys = _systems[i];
		SYS_ASSERT(sys != NULL);
		sys->Quit(engine);
	}
}

void System_Manager::AddSystem(System* system)
{
	SYS_ASSERT(_systems_added < MAX_NUM_SYSTEMS);
	_systems[_systems_added] = system;
	_systems_added++;
}

void System_Manager::DoJob(Engine* engine)
{
	_systems_now = _systems_added;
	sort_systems(_systems, _systems_now);

	// First pass for init systems
	for (size_t i = 0; i < _systems_now; i++)
	{
		System* sys = _systems[i];
		SYS_ASSERT(sys != NULL);
		if (sys->flags & SystemFlags_InitMe)
		{
			sys->Init(engine);
			sys->flags &= ~SystemFlags_InitMe;
		}
	}

	// Update pass
	for (size_t i = 0; i < _systems_now; i++)
	{
		System* sys = _systems[i];
		SYS_ASSERT(sys != NULL);
		if ((sys->flags & SystemFlags_Disabled) == 0)
		{
			sys->DoJob(engine);
		}
	}

	// Last pass to remove systems
	for (size_t i = 0; i < _systems_now; i++)
	{
		System* sys = _systems[i];
		SYS_ASSERT(sys != NULL);
		if (sys->flags & SystemFlags_RemoveMe)
		{
			sys->Quit(engine);
			sys->flags &= ~SystemFlags_RemoveMe;
		}
	}
}