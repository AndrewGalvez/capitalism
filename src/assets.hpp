#pragma once
#include "raylib.h"

extern Texture2D tileset_01;
extern Texture2D tileset_02;
extern Texture2D tileset_04;
extern Texture2D tileset_05;
extern Texture2D tileset_b;

inline void LoadAssets() {
  tileset_01 = LoadTexture("assets/Tilesets/A1.png");
  tileset_02 = LoadTexture("assets/Tilesets/A2.png");
  tileset_04 = LoadTexture("assets/Tilesets/A4.png");
  tileset_05 = LoadTexture("assets/Tilesets/A5.png");
  tileset_b = LoadTexture("assets/Tilesets/B.png");
}
