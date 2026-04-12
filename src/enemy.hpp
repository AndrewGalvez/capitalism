#pragma once
#include "assets.hpp"
#include "global.hpp"
#include "raylib.h"

class Enemy {
public:
  Rectangle rect = {0, 0, Const_Map::tile_size, Const_Map::tile_size};
  int anim_frame = 0, anim_frame_real = 0, anim_frame_real_max = 0, facing = 0;

  Enemy(Rectangle rect) : rect(rect) {};

  void draw() {
    Rectangle source = {Const_Enemy::sprite_unit_px * anim_frame_real,
                        Const_Enemy::sprite_unit_px *
                            (facing + Const_Enemy::sprite_sheet_facing_offset),
                        Const_Enemy::sprite_unit_px,
                        Const_Enemy::sprite_unit_px};
    DrawTexturePro(characters, source, rect, {0, 0}, 0.0f, WHITE);
  }
};
