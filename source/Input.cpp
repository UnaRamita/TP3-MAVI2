#include "Input.h"
// la idea de esto es si despues quiero poner otras teclas o manejar por ejemplo tiempo precionado o algo asi hacerlo desde aca aunque ahora mismo es mas o menos lo mismo que manejarlo directamente en el game
bool InputManager::SpacePressed() {
    return IsKeyPressed(KEY_SPACE);
}
// veo si los ocupo para la direccion del lanzamiento aunque no lo pide la consigna
bool InputManager::LeftDown() {
    return IsKeyDown(KEY_LEFT);
}

bool InputManager::RightDown() {
    return IsKeyDown(KEY_RIGHT);
}
