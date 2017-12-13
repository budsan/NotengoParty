#ifdef SDL_IMPL

#include "Engine.h"
#include "System.h"
#include "SDL_CommonImpl.h"

#ifdef ALLOC_COUNT

size_t debug_allocations = 0;

void _SysDebugIncrMalloc()
{
	debug_allocations++;
}

void _sysDebugDecrMalloc()
{
	debug_allocations--;
}

#endif

void System_Init(Engine* engine)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK);
	IOThread_Init();
}

void System_Update(Engine* engine)
{
	Input_SDL_JoysticksResetState();

	// Window events //
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		bool handled = ImGui_ImplSdl_ProcessEvent(&event);
		if (handled)
			continue;

		switch (event.type)
		{
		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_CLOSE:
				engine->Close();
				handled = true;
				break;
			}
			break;
		case SDL_JOYDEVICEADDED:
			Input_SDL_Event_JoyDeviceAdded(&event);
			break;
		case SDL_JOYDEVICEREMOVED:
			Input_SDL_Event_JoyDeviceRemoved(&event);
			break;
		case SDL_JOYBUTTONDOWN:
			Input_SDL_Event_JoyButtonDown(&event);
			break;
		case SDL_JOYBUTTONUP:
			Input_SDL_Event_JoyButtonUp(&event);
			break;
		case SDL_JOYHATMOTION:
			Input_SDL_Event_JoyHatMotion(&event);
			break;
		case SDL_JOYAXISMOTION:
			Input_SDL_Event_JoyAxisMotion(&event);
			break;
		}
	}
}

void System_Quit(Engine* engine)
{
	IOThread_Destroy();
	SDL_Quit();

#ifdef ALLOC_COUNT
	SYS_ASSERT(debug_allocations == 0);
#endif
}

uint32_t System_Ticks()
{
	return SDL_GetTicks();
}

void System_Sleep(uint32_t ticks)
{
	SDL_Delay(ticks);
}

const char* System_GetClipboardText()
{
	return SDL_GetClipboardText();
}

bool System_SetClipboardText(const char *text)
{
	return SDL_SetClipboardText(text) < 0 ? false : true;
}

void* SysMalloc(size_t size)
{
	SYS_DEBUG_INCR_ALLOC;
	return malloc(size);
}

void* SysRealloc(void* ptr, size_t size)
{
	SYS_DEBUG_INCR_ALLOC;
	return realloc(ptr, size);
}

void SysFree(void* ptr)
{
	free(ptr);
	SYS_DEBUG_DECR_ALLOC;
}

ThreadType Thread_Create(ThreadFunction func, const char* name, void* data)
{
	SDL_Thread *thread = SDL_CreateThread(func, name, data);
	return (ThreadType) thread;
}

void Thread_Wait(ThreadType thread, int* result)
{
	SDL_Thread *thread_impl = (SDL_Thread*)thread;
	SDL_WaitThread(thread_impl, result);
}

MutexType Mutex_Create()
{
	return (MutexType) SDL_CreateMutex();
}
void Mutex_Destroy(MutexType mutex)
{
	SDL_mutex* mutex_impl = (SDL_mutex*)mutex;
	SDL_DestroyMutex(mutex_impl);
}

int Mutex_Lock(MutexType mutex)
{
	SDL_mutex* mutex_impl = (SDL_mutex*)mutex;
	return SDL_LockMutex(mutex_impl) < 0 ? Mutex_Error : Mutex_Ok;
}

int Mutex_Unlock(MutexType mutex)
{
	SDL_mutex* mutex_impl = (SDL_mutex*)mutex;
	return SDL_UnlockMutex(mutex_impl) < 0 ? Mutex_Error : Mutex_Ok;
}

int Mutex_TryLock(MutexType mutex)
{
	SDL_mutex* mutex_impl = (SDL_mutex*)mutex;
	int result = SDL_TryLockMutex(mutex_impl);
	return result < 0 ? Mutex_Error : result;
}

CondVarType CondVar_Create()
{
	SDL_cond* cond_impl = SDL_CreateCond();
	return (CondVarType) cond_impl;
}

void CondVar_Destroy(CondVarType condvar)
{
	SDL_cond* cond_impl = (SDL_cond*) condvar;
	SDL_DestroyCond(cond_impl);
}

int CondVar_SignalOne(CondVarType condvar)
{
	SDL_cond* cond_impl = (SDL_cond*)condvar;
	return SDL_CondSignal(cond_impl) < 0 ? CondVar_Error : CondVar_Ok;
}

int CondVar_SignalAll(CondVarType condvar)
{
	SDL_cond* cond_impl = (SDL_cond*)condvar;
	return SDL_CondBroadcast(cond_impl) < 0 ? CondVar_Error : CondVar_Ok;
}

int CondVar_Wait(CondVarType condvar, MutexType mutex)
{
	SDL_cond* cond_impl = (SDL_cond*)condvar;
	SDL_mutex* mutex_impl = (SDL_mutex*)mutex;
	return SDL_CondWait(cond_impl, mutex_impl) < 0 ? CondVar_Error : CondVar_Ok;
}

int Condvar_WaitFor(CondVarType condvar, MutexType mutex, uint32_t ticks)
{
	SDL_cond* cond_impl = (SDL_cond*)condvar;
	SDL_mutex* mutex_impl = (SDL_mutex*)mutex;

	int result = SDL_CondWaitTimeout(cond_impl, mutex_impl, ticks);
	return result < 0 ? CondVar_Error : result;
}

#endif