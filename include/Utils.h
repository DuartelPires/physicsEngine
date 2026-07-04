#pragma once
#include <raylib.h>
#include <vector>
#include <memory>

class BoxRectangle;
class CirclePlayer;

void tryDrawRectangle(const Vector2& firstVertice, Vector2& secondVertice, bool& isDrawing, std::vector<std::unique_ptr<BoxRectangle>>& boxList, Camera2D& camera);
void checkCommands(bool& isDrawing, Vector2& firstVertice, std::vector<std::unique_ptr<BoxRectangle>>& boxList, bool& isFollowingPlayer, Camera2D& camera);
void createOutsideAngledBox(std::vector<std::unique_ptr<BoxRectangle>>& boxList, float width, float height);
void DrawControls();
