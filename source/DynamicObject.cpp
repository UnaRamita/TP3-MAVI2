#include "DynamicObject.h"

DynamicObject::DynamicObject(b2World* wrld, Vector2 pos, Vector2 siz, float ang, Color col)
    : world(wrld), position(pos), size(siz), angle(ang), color(col), body(nullptr), type(ShapeType::BOX) {
}//default a box, pero se puede cambiar con init, tal vez debería ser un parámetro del constructor

void DynamicObject::init(ShapeType shape) {
    type = shape;

    // definicion del cuerpo (Cuerpo Dinámico)
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    // paso a metros usando sclae
    bodyDef.position.Set(position.x / SCALE, position.y / SCALE);
    bodyDef.angle = angle;
    

    // definicion de la forma y fixture
    b2FixtureDef fixtureDef;

    //punteros para las formas
    b2PolygonShape boxShape;
    b2CircleShape circleShape;

    if (type == ShapeType::BOX) {
        boxShape.SetAsBox((size.x / 2.0f) / SCALE, (size.y / 2.0f) / SCALE);
        fixtureDef.shape = &boxShape;
    }
    else if (type == ShapeType::CIRCLE) {
        // En el caso del circulo, uso size.x como el diametro
        circleShape.m_radius = (size.x / 2.0f) / SCALE;
        fixtureDef.shape = &circleShape;
    }

    // propiedades fisicas
    fixtureDef.density = PROYECTILE_DENSITY;     // masa basicamente
    fixtureDef.friction = PROYECTILE_FRICTION;   // resistencia al deslizamiento
    fixtureDef.restitution = PROYECTILE_BOUNCINESS; // rebote
    //aplicamos todo
    body = world->CreateBody(&bodyDef);
    body->CreateFixture(&fixtureDef);
}

void DynamicObject::applyImpulse(Vector2 impulse) {
    // impulsos producen un cambio inmediato en la velocidad como si fuece un salto o un golpe
    if (body) {
        body->ApplyLinearImpulseToCenter(b2Vec2(impulse.x, impulse.y), true);
    }
}

void DynamicObject::draw() {

    b2Vec2 pos = body->GetPosition();
    float ang = body->GetAngle() * RAD2DEG;
    //esto por que de momento no estoy usando texturas
    if (type == ShapeType::BOX) {
        DrawRectanglePro(
            { pos.x * SCALE, pos.y * SCALE, size.x, size.y },
            { size.x / 2.0f, size.y / 2.0f },
            ang,
            color
        );
    }
    else if (type == ShapeType::CIRCLE) {
        // dibujo el circulo
        DrawCircleV({ pos.x * SCALE, pos.y * SCALE }, size.x / 2.0f, color);
    }
}

DynamicObject::~DynamicObject() {
    if (body) world->DestroyBody(body);
}