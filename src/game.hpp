#pragma once
#include "assets.hpp"
#include "global.hpp"
#include "map.hpp"
#include "player.hpp"
#include "raylib.h"
#include "utils.hpp"
#include <raymath.h>

class Game {
public:
  SceneTransitionFade from_main_menu_transition =
      SceneTransitionFade(16, DARKGREEN, ColorAlpha(DARKGREEN, 0));
  Camera2D gamecam;
  MapTile map[Const_Map::size][Const_Map::size];

  Player player;

  Game() {
    gamecam.target = {player.rect.x + player.rect.width / 2,
                      player.rect.y + player.rect.height / 2};
    gamecam.offset = {Const_Render::width / 2.0f, Const_Render::height / 2.0f};
    gamecam.rotation = 0.0f;
    gamecam.zoom = Const_Camera::initial_zoom;

    for (int y = 0; y < Const_Map::size; y++) {
      for (int x = 0; x < Const_Map::size; x++) {
        if (Vector2Distance({(float)x + Const_Map::cell_center_offset,
                             (float)y + Const_Map::cell_center_offset},
                            {(float)Const_Map::center,
                             (float)Const_Map::center}) >
            Const_Map::spawn_safe_radius) {
          map[y][x] = MapTile(MAP_TILE_SOURCE_GRASS);
          if (GetRandomValue(Const_Map::tree_spawn_roll_min,
                             Const_Map::tree_spawn_roll_max) ==
              Const_Map::tree_spawn_roll_hit) {
            map[y][x] = MapTile(MAP_TILE_SOURCE_TREE);
          }
        } else {
          map[y][x] = MapTile(MAP_TILE_SOURCE_STONE);
        }
      }
    }

    for (int y = 0; y < Const_Map::size; y++) {
      for (int x = 0; x < Const_Map::size; x++) {
        MapTileSourceName n = map[y - 1][x].name;
        MapTileSourceName e = map[y][x + 1].name;
        MapTileSourceName s = map[y + 1][x].name;
        MapTileSourceName w = map[y][x - 1].name;
        map[y][x].fix(n, e, s, w);
      }
    }
  }

  void update(float dt) {
    if (!from_main_menu_transition.finished) {
      from_main_menu_transition.update();
    }

    player.update(map, dt, gamecam);
  }

  void draw() {
    BeginMode2D(gamecam);

    for (int i = 0; i < Const_Map::size; i++) {
      for (int j = 0; j < Const_Map::size; j++) {
        Rectangle source = {0, 0, 32, 32};
        Rectangle dest = {(i - Const_Map::center) * Const_Map::tile_size,
                          (j - Const_Map::center) * Const_Map::tile_size,
                          Const_Map::tile_size, Const_Map::tile_size};
        if (map[j][i].name == MAP_TILE_SOURCE_TREE) {
          DrawTexturePro(tileset_02, {0, 0, 32, 32}, dest, {0, 0}, 0, WHITE);
        }
        DrawTexturePro(*map[j][i].image, map[j][i].source, dest, {0, 0}, 0,
                       WHITE);
      }
    }

    player.draw();

    EndMode2D();

    if (!from_main_menu_transition.finished) {
      DrawRectangle(0, 0, Const_Render::width, Const_Render::height,
                    from_main_menu_transition.getColor());
    }
  }
};
