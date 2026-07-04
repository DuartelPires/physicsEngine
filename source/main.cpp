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
  float screenWidth = 800.0f;
  float screenHeight = 600.0f;

  //camera
  Camera2D camera = {};
  camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
  camera.target = { screenWidth / 2.0f, screenHeight / 2.0f };
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;
  bool isFollowingPlayer = false;

  //variaveis para desenhar retangulo com rato
  Vector2 firstVertice = {0.0f, 0.0f};
  Vector2 secondVertice = firstVertice;
  bool isDrawing = false;


  std::vector<std::unique_ptr<BoxRectangle>> Rectangles;
  
  InitWindow(static_cast<int>(screenWidth), static_cast<int>(screenHeight), "Physics engine");
  SetTargetFPS(60);

  auto circle = std::make_unique<CirclePlayer>(screenWidth / 2.0f, screenHeight / 2.0f);

  createOutsideAngledBox(Rectangles, screenWidth, screenHeight);

  HideCursor();

  while(!WindowShouldClose()) {

    checkCommands(isDrawing, firstVertice, Rectangles, isFollowingPlayer, camera);

    circle->move();

    for(const auto& rectangle : Rectangles) {
      circle->simulate(*rectangle);
    }

    // atualiza o target da camera para o circulo
    if(isFollowingPlayer) {
      camera.target = { circle->getX(), circle->getY() };
    } else {
      camera.target = { screenWidth / 2.0f, screenHeight / 2.0f };
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawControls();
    BeginMode2D(camera);

    for(const auto& rectangle : Rectangles) {
      rectangle->Draw();
    }

    tryDrawRectangle(firstVertice, secondVertice, isDrawing, Rectangles, camera);
    circle->Draw();

    EndMode2D();

    // UI em screen space (nao afetada pela camera)
    circle->DrawUI();
    DrawFPS(10, 10);

    EndDrawing();
  }


  CloseWindow();
  return 0;
}
