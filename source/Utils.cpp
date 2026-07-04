#include "Utils.h"
#include "BoxRectangle.h"
#include "CirclePlayer.h"
#include <raylib.h>
#include <algorithm>
#include <cmath>

void tryDrawRectangle(const Vector2& firstVertice, Vector2& secondVertice, bool& isDrawing, std::vector<std::unique_ptr<BoxRectangle>>& boxList, Camera2D& camera){
  if(!isDrawing) return;
  secondVertice = GetScreenToWorld2D(GetMousePosition(), camera);

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

void checkCommands(bool& isDrawing, Vector2& firstVertice, std::vector<std::unique_ptr<BoxRectangle>>& boxList, bool& isFollowingPlayer,  Camera2D& camera){
    //hides cursor
    if(IsKeyPressed(KEY_H)){
      if(IsCursorHidden()) ShowCursor();
      else HideCursor();
    }
    //começa o desenho ao pressionar
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      isDrawing = true;
      firstVertice = GetScreenToWorld2D(GetMousePosition(), camera);
    }
    //undo last added box
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_Z)) {
      if(boxList.size() > 4){
        boxList.pop_back();
      }
    }
    //camera follows ball
    if(IsKeyPressed(KEY_F)){
      if(isFollowingPlayer){
        isFollowingPlayer = false;
      }else{
        isFollowingPlayer = true;
      }
    }
    //adds or removes zoom
    if (IsKeyDown(KEY_J))
      if((camera.zoom + 0.1f) <= 4 ){
        camera.zoom += 0.01f;
      }

    if (IsKeyDown(KEY_K))
      if((camera.zoom - 0.1f )  >= 0){
        camera.zoom -= 0.01f;
      }
}

void createOutsideAngledBox(std::vector<std::unique_ptr<BoxRectangle>>& boxList, float width, float height){
  int boxWidth = 1600;
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

  void DrawControls(){
    DrawText("Change focus: F", 10, 70, 20, GREEN);
    DrawText("Zoom: J", 10, 90, 20, GREEN);
    DrawText("Unzoom: K", 10, 110, 20, GREEN);
    DrawText("Show Cursor: H", 10, 130, 20, GREEN);
    DrawText("Add block: Click and drag", 10, 150, 20, GREEN);
    DrawText("Undo: Ctrl + Z", 10, 170, 20, GREEN);
  }
