#pragma once

struct FileReadAsync
{
	void* data;
	size_t size;
	bool completed;
};

void File_LoadToMemoryAsync(const char* filename, FileReadAsync* asyncOp);
