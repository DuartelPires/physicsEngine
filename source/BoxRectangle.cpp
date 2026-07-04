#include "BoxRectangle.h"
#include <cmath>

BoxRectangle::BoxRectangle() 
    : x(0.0f), y(0.0f), width(0), height(0), angle(0.0f), rad(0.0f) {
    rAxisX.x = 1.0f;
    rAxisX.y = 0.0f;
    rAxisY.x = 0.0f;
    rAxisY.y = 1.0f;
}

BoxRectangle::BoxRectangle(float inicialX, float inicialY, int initialWidth, int initialHeight, float initialAngle) 
    : x(inicialX), y(inicialY), width(initialWidth), height(initialHeight), angle(initialAngle) {

    rad = angle * DEG2RAD;
    rAxisX.x = std::cos(rad);
    rAxisX.y = std::sin(rad);
    rAxisY.x = -std::sin(rad);
    rAxisY.y = std::cos(rad);
}

void BoxRectangle::Draw() {
    Rectangle rec = { x, y, static_cast<float>(width), static_cast<float>(height) };
    Vector2 origin = { static_cast<float>(width) / 2.0f, static_cast<float>(height) / 2.0f };
    DrawRectanglePro(rec, origin, angle, MAROON);
}
