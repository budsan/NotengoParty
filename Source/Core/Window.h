#pragma once

struct Engine;
typedef void* WindowType;

void Window_Create(Engine* engine, const char* name, int w, int h);
void Window_Destroy(Engine* engine);

void Window_SetTitle(Engine* engine, const char* title);
void Window_GetSize(Engine* engine, int* width, int* height);

const char** Window_GetResolutions(Engine* engine, int* res_count, int* current);
void Window_SetResolution(Engine* engine, const char* resolution);

const char** Window_GetModes(Engine* engine, int* modes_count, int* current);
void Window_SetMode(Engine* engine, const char* mode);