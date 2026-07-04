#include "CirclePlayer.h"
#include "BoxRectangle.h"
#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <algorithm>

CirclePlayer::CirclePlayer() : x(0.0f), y(0.0f) {}

CirclePlayer::CirclePlayer(float inicialX, float inicialY) : x(inicialX), y(inicialY) {}

void CirclePlayer::Draw() {
    DrawCircle(x, y, radius, BLACK);
    DrawCircle(x, y, radius - 4, RAYWHITE);
    DrawText(TextFormat("X: %i", static_cast<int>(x)), 10, 30, 20, GREEN);
    DrawText(TextFormat("Y: %i", static_cast<int>(y)), 10, 50, 20, GREEN);
}

void CirclePlayer::move() {
    x += speedX;
    y += speedY;
}

void CirclePlayer::simulate(const BoxRectangle& box) {
    // vetores diretores da caixa
    float rad = box.getRad();
    Vector2 rAxisX = box.getRAxisX();
    Vector2 rAxisY = box.getRAxisY();

    //vetor do centro da caixa até o centro da bola
    Vector2 d = { x - box.getX(), y - box.getY() };

    //distância escalar
    float ax = Vector2DotProduct(d, rAxisX);
    float ay = Vector2DotProduct(d, rAxisY);

    float halfW = box.getWidth() / 2.0f;
    float halfH = box.getHeight() / 2.0f;

    float closestX = std::max(-halfW, std::min(ax, halfW));
    float closestY = std::max(-halfH, std::min(ay, halfH));

    //distancia entre bola e o ponto mais proximo na caixa)
    float distX = ax - closestX;
    float distY = ay - closestY;

    float distanceSquared = (distX * distX) + (distY * distY);

    if (distanceSquared < (radius * radius)) {
        float distance = std::sqrt(distanceSquared);
        if (distance == 0.0f) return;

        // Vetor normal da colisão no espaço local
        Vector2 localNormal = { distX / distance, distY / distance };

        Vector2 normal = {
            localNormal.x * rAxisX.x + localNormal.y * rAxisY.x,
            localNormal.x * rAxisX.y + localNormal.y * rAxisY.y
        };

        float overlap = radius - distance;
        x += normal.x * overlap;
        y += normal.y * overlap;

        Vector2 vel = { speedX, speedY };
        float dotProduct = Vector2DotProduct(vel, normal);

        speedX = vel.x - 2.0f * dotProduct * normal.x;
        speedY = vel.y - 2.0f * dotProduct * normal.y;
    }
}
