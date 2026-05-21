#pragma once
#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"
#include <box2d.h>
#include "Config.h"

class staticObjects
{
public:
	staticObjects(b2World* world, Vector2 pos, Vector2 size);

	void init();
	void draw();
	~staticObjects();

private:
	b2Body* body;
	b2World* world;

	Vector2 objSize;
	Vector2 objPos;
};

