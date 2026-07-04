#include "Utils.h"
#include "BoxRectangle.h"
#include <raylib.h>
#include <algorithm>
#include <cmath>

void tryDrawRectangle(const Vector2& firstVertice, Vector2& secondVertice, bool& isDrawing, std::vector<std::unique_ptr<BoxRectangle>>& boxList){
  if(!isDrawing) return;
  
  secondVertice = GetMousePosition();

  float x = std::min(firstVertice.x, secondVertice.x);
  float y = std::min(firstVertice.y, secondVertice.y);
  float width = std::abs(firstVertice.x - secondVertice.x);
  float height = std::abs(firstVertice.y - secondVertice.y);

  //desenha o preview
  DrawRectangle((int)x, (int)y, (int)width, (int)height, Fade(MAROON, 0.5f));

  //ao soltar o botão esquerdo, finaliza o desenho
  if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
    isDrawing = false;
    if (width > 5.0f && height > 5.0f) {
      boxList.push_back(std::make_unique<BoxRectangle>(x + width/2.0f, y + height/2.0f, (int)width, (int)height, 0.0f));
    }
  }
}

void checkCommands(bool& isDrawing, Vector2& firstVertice,std::vector<std::unique_ptr<BoxRectangle>>& boxList){
    if(IsKeyPressed(KEY_H)){
      if(IsCursorHidden()) ShowCursor();
      else HideCursor();
    }
    //começa o desenho ao pressionar
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      isDrawing = true;
      firstVertice = GetMousePosition();
    }
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_Z)) {
      if(boxList.size() > 4){
        boxList.pop_back();
      }
    }
}

void createOutsideAngledBox(std::vector<std::unique_ptr<BoxRectangle>>& boxList, float width, float height){
  int boxWidth = 400;
  int boxHeight = 15;

  float cx = width / 2.0f;
  float cy = height / 2.0f;

  float d = (boxWidth / 2.0f) * 0.7071f; // 0.7071 cosseno/seno de 45 graus
 
  auto topRectangle    = std::make_unique<BoxRectangle>(cx + d, cy - d, boxWidth + boxHeight, boxHeight, 45.0f);
  auto bottomRectangle = std::make_unique<BoxRectangle>(cx - d, cy + d, boxWidth + boxHeight, boxHeight, 45.0f);
  auto leftRectangle   = std::make_unique<BoxRectangle>(cx - d, cy - d, boxHeight, boxWidth + boxHeight, 45.0f);
  auto rightRectangle  = std::make_unique<BoxRectangle>(cx + d, cy + d, boxHeight, boxWidth + boxHeight, 45.0f);
 
  boxList.push_back(std::move(topRectangle));
  boxList.push_back(std::move(leftRectangle));
  boxList.push_back(std::move(rightRectangle));
  boxList.push_back(std::move(bottomRectangle));
}
