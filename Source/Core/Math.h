#pragma once

struct Vec2
{
	float x, y;
	Vec2() { x = y = 0.0f; }
	Vec2(float _x, float _y) { x = _x; y = _y; }
};

struct Vec3
{
	float x, y, z;
	Vec3() { x = y = z = 0.0f; }
	Vec3(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }
};

struct Vec4
{
	float x, y, z, w;
	Vec4() { x = y = z = w = 0.0f; }
	Vec4(float _x, float _y, float _z, float _w) { x = _x; y = _y; z = _z; w = _w; }
};