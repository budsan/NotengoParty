#pragma once

#include <stdint.h>

#include "Math.h"
#include "LightVector.h"

struct Engine;
typedef void* RendererType;

#define RNDR_BLEND(SRC, DST) (SRC | (DST << 4))
#define RNDR_GET_BLEND_SRC(X) (0x0F & X);
#define RNDR_GET_BLEND_DST(X) ((0xF0 & X) >> 4)
#define RNDR_SET_BLEND_SRC(X, SRC) (SRC | (0xF0 & X))
#define RNDR_SET_BLEND_DST(X, DST) ((0x0F & X) | (DST << 4))

enum BlendFunc
{
	BlendZero,
	BlendOne,
	BlendSourceColor,
	BlendOneMinusSourceColor,
	BlendSourceAlpha,
	BlendOneMinusSourceAlpha,
	BlendDestAlpha,
	BlendOneMinusDestAlpha,
	BlendSourceAlphaSaturate,
};

enum DepthTestFunc
{
	DepthTestNever,
	DepthTestLess,
	DepthTestEqual,
	DepthTestLessEqual,
	DepthTestGreater,
	DepthTestNotEqual,
	DepthTestGreaterEqual,
	DepthTestAlways
};

struct RendererState
{
	bool Blend : 1;
	bool DepthTest : 1;

	uint8_t BlendFunc;
	uint8_t DepthTestFunc;
};

struct DrawVertex
{
	Vec2 pos;
	Vec2 uv;
	uint32_t col;
};

struct DrawCamera
{
	float x;
	float y;
	float zoom;
};

struct DrawCmd
{
	uint32_t ElemStart;
	uint32_t ElemCount;
};

struct DrawList
{
	typedef uint16_t IdxType;

	LightVector<DrawVertex> vtx_buffer;
	LightVector<IdxType> idx_buffer;
	LightVector<DrawCmd> cmds;
	DrawCamera cam;

	DrawList() { Clear(); }
	void Clear()
	{
		// We use resize instead of clear to avoid free memory.
		vtx_buffer.resize(0);
		idx_buffer.resize(0);
		cmds.resize(1);
		cmds[0].ElemCount = 0;
		cmds[0].ElemStart = 0;
	}
};

void Renderer_Create(Engine* engine);
void Renderer_Destroy(Engine* engine);

void Renderer_ImGui_NewFrame(Engine* engine);

void Renderer_Clear(Engine* engine, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void Renderer_DrawLogic(Engine* engine, DrawList* drawlist);
void Renderer_Present(Engine* engine);

void Renderer_SetViewport(float width, float height);


