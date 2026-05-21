#include "Game.h"
Game::Game() : physics(nullptr)
{
	ground = nullptr;
	wallLeft = nullptr;
	wallRight = nullptr;

}

void Game::inits() {
	//iniciamos el mundo fisico
	physics = new physicsManager();

	b2World* world = physics->GetWorld();
	//iniciamos los objetos estaticos
	// Piso
	ground = new staticObjects(world, { (float)SCREEN_WIDTH / 2.0f, (float)SCREEN_HEIGHT - 20.0f }, { (float)SCREEN_WIDTH, 40.0f });
	ground->init();

	// Pared Izquierda
	wallLeft = new staticObjects(world, { 10.0f, (float)SCREEN_HEIGHT / 2.0f }, { 20.0f, (float)SCREEN_HEIGHT });
	wallLeft->init();

	// Pared Derecha
	wallRight = new staticObjects(world, { (float)SCREEN_WIDTH - 10.0f, (float)SCREEN_HEIGHT / 2.0f }, { 20.0f, (float)SCREEN_HEIGHT });
	wallRight->init();

	//los pongo en la lista para dibujarlos dsp
	environment.push_back(ground);
	environment.push_back(wallLeft);
	environment.push_back(wallRight);

	preview = new Preview({ 100.0f, (float)SCREEN_HEIGHT - 60.0f });
	//unidad 3 joints
	//resortes (voy a hacer 2, son iguales solo que en diferente direccion)
	//1er resorte
	bouncers.push_back(new SpringBouncer(world, { (float)SCREEN_WIDTH/2.0f+100.0f, (float)SCREEN_HEIGHT - 100.0f}, {100.0f, 20.0f}, 0.0f, RED));
	//2do resorte
	bouncers.push_back(new SpringBouncer(world, { (float)SCREEN_WIDTH -75.0f, (float)SCREEN_HEIGHT - 150.0f }, { 100.0f, 20.0f }, -90.0f, BLUE));
}

void Game::inputs() {
	if (InputManager::SpacePressed()) {
		// Paso el angulo de la preview
		float angleInRad = preview->GetAngle() * DEG2RAD;
		//para el size en vez de pasar el radio, paso el diametro (radio*2)
		float diameter = (PROYECTILE_RADIUS * SCALE) * 2.0f;

		DynamicObject* projectile = new DynamicObject(physics->GetWorld(), preview->GetPosition(), {diameter,diameter}, angleInRad, GRAY );
		//le digo que es un circulo
		projectile->init(ShapeType::CIRCLE);

		//aca ya esta creado el proyectil y le aplico el impulso para lanzarlo, dsp lo dibujo en el draw
		float launchPower = 15.0f; //si quisiera poner algun input para variar la potencia del lanzamiento, pondria esto en otro lado
		//creo el vector para el impulso, con coseno y seno para que sea en la direccion de la preview
		Vector2 impulse = {cosf(angleInRad) * launchPower, sinf(angleInRad) * launchPower};
		//aplico el impulso al proyectil
		projectile->applyImpulse(impulse);
		//lo agrego a la lista de proyectiles para dibujarlo dsp
		projectiles.push_back(projectile);

	}
	if (InputManager::LeftDown()) {
		//aca podria manejar la "rotacion" de la catapulta
		preview->Rotate(-5.0f); // Rota 5 grados a la izquierda
	}
	if (InputManager::RightDown()) {
		//aca podria manejar la "rotacion" de la catapulta
		preview->Rotate(5.0f); // Rota 5 grados a la derecha
	}
}

void Game::load() {
	//actualizamos la fisica
	physics->Update();
	//draws
	DrawText("Use LEFT and RIGHT arrows to aim your shot, SPACE to shoot", 20, 10, 18, BLUE);
	//statics
	for (auto obj : environment) obj->draw();
	//dynamics (disparo de la catapulta)
	preview->Draw();
	for (auto proj : projectiles) proj->draw();
	for (auto bouncer : bouncers) bouncer->draw();
}

void Game::run() {
	
	while (!WindowShouldClose())
	{
		inputs();
		BeginDrawing();
		ClearBackground(RAYWHITE);

		load();

		EndDrawing();
	}
	
}
Game::~Game()
{
}