#pragma once
#ifndef NDEBUG
#include <vld.h>
#endif
#include "raylib.h"
#include <box2d.h>
#include <vector>
#include "DynamicObject.h"
#include "PhysicsManager.h"
#include "StaticObjects.h"
#include "Config.h"
#include "Input.h"
#include "Preview.h"
#include "SpringBouncer.h"

class Game
{
public:
	Game();
	~Game();

	void inits();

	void run();

private:

	staticObjects* ground;
	staticObjects* wallLeft;
	staticObjects* wallRight;

	Preview* preview;

	void load();
	void inputs();

	physicsManager* physics;
	std::vector<staticObjects*> environment;//ambiente, suelo y paredes, dsp capaz le cambio el nombre de esto
	std::vector<DynamicObject*> projectiles; // Lista para almacenar los proyectiles lanzados

	//unidad 3 joints
	std::vector<SpringBouncer*> bouncers; // lista para almacenar los resortes que creo

};