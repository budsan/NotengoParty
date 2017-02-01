#pragma once

#include <stdio.h>

struct Engine;

void System_Init(Engine* engine);
void System_Update(Engine* engine);
void System_Quit(Engine* engine);

void* SysMalloc(size_t size);
void SysFree(void* ptr);


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