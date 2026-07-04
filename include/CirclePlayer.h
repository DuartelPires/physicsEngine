#pragma once

class BoxRectangle;

class CirclePlayer {
  private:
    float x;
    float y;
    float radius = 20.0f;
    float speedX = 6.0f;
    float speedY = 8.0f;

  public:
    CirclePlayer();
    CirclePlayer(float inicialX, float inicialY);

    void Draw();
    void move();
    void simulate(const BoxRectangle& box);
};
