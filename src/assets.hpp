#pragma once
#include "raylib.h"

extern Texture2D tileset_01;
extern Texture2D tileset_02;
extern Texture2D tileset_04;
extern Texture2D tileset_05;
extern Texture2D tileset_b;
extern Texture2D characters;

inline void LoadAssets() {
  tileset_01 = LoadTexture("assets/Tilesets/A1.png");
  tileset_02 = LoadTexture("assets/Tilesets/A2.png");
  tileset_04 = LoadTexture("assets/Tilesets/A4.png");
  tileset_05 = LoadTexture("assets/Tilesets/A5.png");
  tileset_b = LoadTexture("assets/Tilesets/B.png");
  characters = LoadTexture("assets/Characters/characters.png");
}

enum PlayerSpriteState { PLAYER_SPRITE_STATE_IDLE, PLAYER_SPRITE_STATE_WALK };

// frame: 0-2
// facing: 0 (down), 1(left), 2(right), 3(up)
inline Rectangle GetPlayerSpriteSource(PlayerSpriteState state, int frame,
                                       int facing) {
  if (frame == 1)
    frame = 2;
  if (state == PLAYER_SPRITE_STATE_IDLE)
    frame = 1;
  return Rectangle{32 * 3 + 32.0f * frame, 32.0f * facing, 32, 32};
};
