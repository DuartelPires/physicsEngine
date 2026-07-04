#pragma once
#include <raylib.h>

class BoxRectangle {
  private:
    float x;
    float y;
    int width;
    int height;
    float angle;
    float rad;
    Vector2 rAxisX;
    Vector2 rAxisY;

  public:
    BoxRectangle();
    BoxRectangle(float inicialX, float inicialY, int initialWidth, int initialHeight, float initialAngle);

    void Draw();

    float getX() const { return x; }
    float getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    float getAngle() const { return angle; }
    float getRad() const { return rad; }
    Vector2 getRAxisX() const { return rAxisX; }
    Vector2 getRAxisY() const { return rAxisY; }
};
