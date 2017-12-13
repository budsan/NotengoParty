#pragma once
#define ALLOC_COUNT

#include <stdio.h>

struct Engine;

void System_Init(Engine* engine);
void System_Update(Engine* engine);
void System_Quit(Engine* engine);

void* SysMalloc(size_t size);
void* SysRealloc(void* ptr, size_t size);
void SysFree(void* ptr);

#ifdef ALLOC_COUNT

#define SYS_DEBUG_INCR_ALLOC _SysDebugIncrMalloc()
#define SYS_DEBUG_DECR_ALLOC _sysDebugDecrMalloc()

void _SysDebugIncrMalloc();
void _sysDebugDecrMalloc();

#else

#define SYS_DEBUG_INCR_MALLOC
#define SYS_DEBUG_DECR_MALLOC

#endif

#define SYS_LOG(...) printf(__VA_ARGS__)

#if defined(SDL_IMPL)

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include "imgui/imgui.h"

#define SYS_ASSERT(...) SDL_assert(__VA_ARGS__)
#else
#error "Not defined platform"
#endif

#define SYS_TICKS_PASSED(A, B)  ((Sint32)((B) - (A)) <= 0)

struct ImPlacementNewDummy {};
inline void* operator new(size_t, ImPlacementNewDummy, void* ptr){ return ptr; }
inline void operator delete(void*, ImPlacementNewDummy, void*) {}
#define SYS_PLACEMENT_NEW(_PTR)  new(ImPlacementNewDummy(), _PTR)

uint32_t System_Ticks();
void System_Sleep(uint32_t ticks);

const char* System_GetClipboardText();
bool System_SetClipboardText(const char *text);

typedef void* ThreadType;
typedef int(*ThreadFunction)(void* data);

ThreadType Thread_Create(ThreadFunction func, const char* name, void* data);
void Thread_Wait(ThreadType thread, int* result);

typedef void* MutexType;

MutexType Mutex_Create();
void Mutex_Destroy(MutexType mutex);

enum
{
	Mutex_Error = -1,
	Mutex_Ok = 0,
	Mutex_TimeOut = 1
};

int Mutex_Lock(MutexType mutex);
int Mutex_Unlock(MutexType mutex);
int Mutex_TryLock(MutexType mutex);

struct LockGuard
{
	MutexType mutex;
	LockGuard(MutexType mutex) : mutex(mutex) { Mutex_Lock(mutex); }
	~LockGuard() { Mutex_Unlock(mutex); }
};

typedef void* CondVarType;

CondVarType CondVar_Create();
void CondVar_Destroy(CondVarType condvar);

enum
{
	CondVar_Error = -1,
	CondVar_Ok = 0,
	CondVar_TimeOut = 1
};

int CondVar_SignalOne(CondVarType condvar);
int CondVar_SignalAll(CondVarType condvar);

int CondVar_Wait(CondVarType condvar, MutexType mutex);
int Condvar_WaitFor(CondVarType condvar, MutexType mutex, uint32_t ticks);


