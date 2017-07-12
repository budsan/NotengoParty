#if SDL_IMPL

#include <SDL.h>
#include <queue>
#include <string>

#include "File.h"
#include "System.h"
#include "LightVector.h"

struct IOThreadTask
{
	std::string filename;
	FileReadAsync* result;
};

struct IOThreadData
{
	bool forceExit;
	std::queue<IOThreadTask> tasks;

	MutexType mutex;
	CondVarType condvar;
};

ThreadType _IOThread = NULL;
IOThreadData _IOThreadData;

void IOThread_LoadToMemory(IOThreadTask& task)
{
	SDL_RWops* f;
	if ((f = SDL_RWFromFile(task.filename.c_str(), "rb")) == NULL)
		goto fail1;
		
	int64_t file_size_signed;
	if (SDL_RWseek(f, 0, SEEK_END) < 0)
		goto fail2;

	file_size_signed = SDL_RWtell(f);
	if (file_size_signed < 0)
		goto fail2;

	if (SDL_RWseek(f, 0, SEEK_SET) < 0)
		goto fail2;

	size_t file_size = file_size_signed;
	void* file_data = SysMalloc(file_size);
	if (file_data == NULL)
		goto fail2;
	
	if (SDL_RWread(f, file_data, 1, file_size) != file_size)
		goto fail3;

	SDL_RWclose(f);
	task.result->completed = true;
	task.result->data = file_data;
	task.result->size = file_size;
	return;

fail3:
	SysFree(file_data);
fail2:
	SDL_RWclose(f);
fail1:
	task.result->completed = true;
	task.result->data = NULL;
	task.result->size = 0;
}

int IOThread_Main(void* data)
{
	IOThreadData* iothread_data = (IOThreadData*)data;
	for(;;)
	{
		IOThreadTask task;
		{
			LockGuard lock(iothread_data->mutex);
			while (iothread_data->tasks.empty() && !iothread_data->forceExit)
				CondVar_Wait(iothread_data->condvar, iothread_data->mutex);

			if (iothread_data->forceExit)
				break;

			task = std::move(iothread_data->tasks.front());
			iothread_data->tasks.pop();
		}
		
		IOThread_LoadToMemory(task);
	}

	CondVar_Destroy(iothread_data->condvar);
	Mutex_Destroy(iothread_data->mutex);

	return 0;
}

void IOThread_Init()
{
	_IOThreadData.forceExit = false;
	_IOThreadData.mutex = Mutex_Create();
	_IOThreadData.condvar = CondVar_Create();
	_IOThread = Thread_Create(IOThread_Main, "IOThread", &_IOThreadData);
}

void IOThread_Destroy()
{
	SYS_ASSERT(_IOThread != NULL);
	_IOThreadData.forceExit = true;
	CondVar_SignalAll(_IOThreadData.condvar);

	int result;
	Thread_Wait(_IOThread, &result);
}

void File_LoadToMemoryAsync(const char* filename, FileReadAsync* asyncOp)
{
	asyncOp->completed = false;
	IOThreadTask task;
	task.filename = filename;
	task.result = asyncOp;
	{
		LockGuard lock(_IOThreadData.mutex);
		_IOThreadData.tasks.push(task);
	}

	CondVar_SignalOne(_IOThreadData.condvar);
}

#endif