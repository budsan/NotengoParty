#ifdef DX11_IMPL

#include "Engine.h"
#include "System.h"

#include "DX11_CommonImpl.h"

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
}

void System_Update(Engine* engine)
{
}

void System_Quit(Engine* engine)
{
}

uint32_t System_Ticks()
{
	return 0;
}

void System_Sleep(uint32_t ticks)
{
}

const char* System_GetClipboardText()
{
	return nullptr;
}

bool System_SetClipboardText(const char *text)
{
	return false;
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
	return nullptr;
}

void Thread_Wait(ThreadType thread, int* result)
{
}

MutexType Mutex_Create()
{
	return nullptr;
}

void Mutex_Destroy(MutexType mutex)
{
}

int Mutex_Lock(MutexType mutex)
{
	return Mutex_Error;
}

int Mutex_Unlock(MutexType mutex)
{
	return Mutex_Error;
}

int Mutex_TryLock(MutexType mutex)
{
	return Mutex_Error;
}

CondVarType CondVar_Create()
{
	return nullptr;
}

void CondVar_Destroy(CondVarType condvar)
{
}

int CondVar_SignalOne(CondVarType condvar)
{
	return CondVar_Error;
}

int CondVar_SignalAll(CondVarType condvar)
{
	return CondVar_Error;
}

int CondVar_Wait(CondVarType condvar, MutexType mutex)
{
	return CondVar_Error;
}

int Condvar_WaitFor(CondVarType condvar, MutexType mutex, uint32_t ticks)
{
	return CondVar_Error;
}

#endif