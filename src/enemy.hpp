#pragma once
#include "assets.hpp"
#include "global.hpp"
#include "map.hpp"
#include "raylib.h"
#include <algorithm>
#include <raymath.h>

inline int getSide(int px, int py, int x, int y, int w, int h) {
  const int nx = (px - x) / w; // normalize to [0,1]
  const int ny = (py - y) / h;

  const int d1 = ny - nx;
  const int d2 = ny - (1 - nx);

  if (d1 < 0 && d2 < 0)
    return 4; // top
  if (d1 > 0 && d2 > 0)
    return 1; // bottom
  if (d1 > 0 && d2 < 0)
    return 2; // left
  return 3;   // right
}

class Enemy {
public:
  Rectangle rect = {0, 0, Const_Map::tile_size, Const_Map::tile_size};
  int anim_frame = 1, anim_frame_real = 0, anim_frame_real_max = 10, facing = 0;
  int anim_dir = 1;
  float speed = 40.0f;

  Enemy(Rectangle rect) : rect(rect) {};

  void draw() {
    Rectangle source = {Const_Enemy::sprite_unit_px * anim_frame,
                        (Const_Enemy::sprite_unit_px * 3.0f) +
                            Const_Enemy::sprite_unit_px * facing,
                        Const_Enemy::sprite_unit_px,
                        Const_Enemy::sprite_unit_px};
    DrawTexturePro(characters, source, rect, {0, 0}, 0.0f, WHITE);
  }

  void update(float dt, Vector2 playercenter,
              MapTile map[Const_Map::size][Const_Map::size]) {
    anim_frame_real++;
    if (anim_frame_real >= anim_frame_real_max) {
      anim_frame_real = 0;
      anim_frame += anim_dir;
      if (anim_frame >= 2 || anim_frame <= 0)
        anim_dir = -anim_dir;
    }

    facing = getSide(playercenter.x, playercenter.y, rect.x, rect.y, rect.width,
                     rect.height);

    Vector2 center = {rect.x + rect.width / 2, rect.y + rect.height / 2};
    Vector2 newpos = Vector2MoveTowards(center, playercenter, speed * dt);

    float newx = newpos.x - rect.width / 2;
    float newy = newpos.y - rect.height / 2;

    auto tileAt = [&](float wx, float wy) -> MapTile & {
      int tx = std::max(
          0, std::min(Const_Map::size - 1,
                      (int)floor(wx / Const_Map::tile_size) + Const_Map::center));
      int ty = std::max(
          0, std::min(Const_Map::size - 1,
                      (int)floor(wy / Const_Map::tile_size) + Const_Map::center));
      return map[ty][tx];
    };

    bool blockX =
        tileAt(newx, rect.y).type == MAP_TILE_TYPE_WALL ||
        tileAt(newx + rect.width, rect.y).type == MAP_TILE_TYPE_WALL ||
        tileAt(newx, rect.y + rect.height).type == MAP_TILE_TYPE_WALL ||
        tileAt(newx + rect.width, rect.y + rect.height).type ==
            MAP_TILE_TYPE_WALL;

    bool blockY =
        tileAt(rect.x, newy).type == MAP_TILE_TYPE_WALL ||
        tileAt(rect.x + rect.width, newy).type == MAP_TILE_TYPE_WALL ||
        tileAt(rect.x, newy + rect.height).type == MAP_TILE_TYPE_WALL ||
        tileAt(rect.x + rect.width, newy + rect.height).type ==
            MAP_TILE_TYPE_WALL;

    if (!blockX)
      rect.x = newx;
    if (!blockY)
      rect.y = newy;
  }
};
