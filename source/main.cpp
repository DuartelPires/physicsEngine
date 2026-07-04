#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <memory>
#include <vector>
#include <utility>
#include <cmath>

#include "Utils.h"
#include "CirclePlayer.h"
#include "BoxRectangle.h"


int main() {
  int screenWidth = 800;
  int screenHeight = 600;

  //variaveis para desenhar retangulo com rato
  Vector2 firstVertice = {0.0f, 0.0f};
  Vector2 secondVertice = firstVertice;
  bool isDrawing = false;

  std::vector<std::unique_ptr<BoxRectangle>> Rectangles;
  
  float screenWidthF = static_cast<float>(screenWidth);
  float screenHeightF = static_cast<float>(screenHeight);
  
  InitWindow(screenWidth, screenHeight, "Physics engine");
  SetTargetFPS(60);

  auto circle = std::make_unique<CirclePlayer>(screenWidthF / 2.0f, screenHeightF / 2.0f);

  createOutsideAngledBox(Rectangles, screenWidthF, screenHeightF);

  HideCursor();

  while(!WindowShouldClose()) {

    checkCommands(isDrawing, firstVertice, Rectangles);

    circle->move();

    for(const auto& rectangle : Rectangles) {
      circle->simulate(*rectangle);
    }

    ClearBackground(RAYWHITE);

    for(const auto& rectangle : Rectangles) {
      rectangle->Draw();
    }

    tryDrawRectangle(firstVertice, secondVertice, isDrawing, Rectangles);
    circle->Draw();

    DrawFPS(10, 10);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
