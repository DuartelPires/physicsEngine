#pragma once
#include <raylib.h>
#include <vector>
#include <memory>

class BoxRectangle;

void tryDrawRectangle(const Vector2& firstVertice, Vector2& secondVertice, bool& isDrawing, std::vector<std::unique_ptr<BoxRectangle>>& boxList);
void checkCommands(bool& isDrawing, Vector2& firstVertice,std::vector<std::unique_ptr<BoxRectangle>>& boxList);
void createOutsideAngledBox(std::vector<std::unique_ptr<BoxRectangle>>& boxList, float width, float height);
