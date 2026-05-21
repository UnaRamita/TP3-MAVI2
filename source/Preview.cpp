#include "Preview.h"

Preview::Preview(Vector2 pos) {
    position = pos;
    angle = -45.0f;    //  apuntando hacia arriba a la derecha
    lineLength = 60.0f; // Largo de la "mira"
    dotsCount = 5;      // Cantidad de puntitos
}

void Preview::Rotate(float amount) {
    angle += amount;
}

void Preview::Draw() {
    // proyectil preview
    // uso el radio definido en Config para que coincida con el real
    DrawCircle(position.x, position.y, (PROYECTILE_RADIUS * SCALE), GRAY);

    //dibujo de la línea punteada (la dirección)
    // convertimos el angulo a radianes para usar cos y sin
    float angleRad = angle * DEG2RAD;

    for (int i = 1; i <= dotsCount; i++) {
        //posición de cada punto
        float dist = (lineLength / dotsCount) * i;
        float dotX = position.x + cosf(angleRad) * dist;
        float dotY = position.y + sinf(angleRad) * dist;

        // dibujamos
        DrawCircle(dotX, dotY, 2.0f, MAROON);
    }
}

Preview::~Preview() {}