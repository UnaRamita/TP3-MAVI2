#include "StaticObjects.h"
staticObjects::staticObjects(b2World* wrld, Vector2 pos, Vector2 size)
{
	body = nullptr;
	world = wrld;
	objSize = size;
	objPos = pos;

}

void staticObjects::init() {
	//definicion del cuerpo (estatico en este caso)
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(objPos.x / SCALE, objPos.y / SCALE);

	//forma y propiedades 
	//forma
	b2PolygonShape groundBox;
	groundBox.SetAsBox((objSize.x / 2.0f) / SCALE, (objSize.y / 2.0f) / SCALE);
	//propiedades
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.friction = 0.5f;     // algo de friccion
	fixtureDef.restitution = 0.2f;  // rebote

	//aplicamos todo
	body = world->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);

}

void staticObjects::draw() {
	//primer llave es el rectangle, segunda llave es el origen de donde se dibuja dsp chequeo que se vea donde quiero capaz le estoy errando x2
	DrawRectanglePro({objPos.x, objPos.y, objSize.x, objSize.y}, { objSize.x / 2.0f, objSize.y / 2.0f }, 0.0f, DARKGRAY);
}
															
staticObjects::~staticObjects()
{
	if (body && world) {
		world->DestroyBody(body);
	}
}