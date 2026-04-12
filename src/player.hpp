#pragma once
#include "assets.hpp"
#include "global.hpp"
#include "map.hpp"
#include "raylib.h"
#include <cmath>

class Player {
public:
  Rectangle rect = {0, 0, Const_Map::tile_size, Const_Map::tile_size};
  Rectangle hitbox = {0, 0, Const_Map::tile_size, Const_Map::tile_size};

  int facing = 0;
  int anim_frame = 0;
  int anim_frame_real_max = Const_Player::animation_frame_real_max;
  int anim_frame_real = 0;
  float speed = Const_Player::speed;
  PlayerSpriteState state;

  void update(MapTile map[Const_Map::size][Const_Map::size], float dt,
              Camera2D &gamecam) {
    this->hitbox = {this->rect.x + ((this->rect.width / Const_Player::sprite_unit_px) *
                                    Const_Player::hitbox_left_units),
                    this->rect.y + ((this->rect.height / Const_Player::sprite_unit_px) *
                                    Const_Player::hitbox_top_units),
                    this->rect.width -
                        ((this->rect.width / Const_Player::sprite_unit_px) *
                         Const_Player::hitbox_right_units),
                    this->rect.height -
                        ((this->rect.height / Const_Player::sprite_unit_px) *
                         Const_Player::hitbox_bottom_units)};

    this->state = PLAYER_SPRITE_STATE_IDLE;

    if (IsKeyDown(KEY_A)) {
      int npxt =
          (int)floor((this->hitbox.x - this->speed * dt) / Const_Map::tile_size) +
          Const_Map::center;
      int npyts[2] = {
          (int)floor(this->hitbox.y / Const_Map::tile_size) + Const_Map::center,
          (int)floor((this->hitbox.y + this->hitbox.height) /
                     Const_Map::tile_size) +
              Const_Map::center};
      if (map[npyts[0]][npxt].type != MAP_TILE_TYPE_WALL &&
          map[npyts[1]][npxt].type != MAP_TILE_TYPE_WALL) {
        this->rect.x -= this->speed * dt;
        this->facing = 1;
        this->state = PLAYER_SPRITE_STATE_WALK;
      }
    } else if (IsKeyDown(KEY_D)) {
      int npxt =
          (int)floor((this->hitbox.x + this->hitbox.width + this->speed * dt) /
                     Const_Map::tile_size) +
          Const_Map::center;
      int npyts[2] = {
          (int)floor(this->hitbox.y / Const_Map::tile_size) + Const_Map::center,
          (int)floor((this->hitbox.y + this->hitbox.height) /
                     Const_Map::tile_size) +
              Const_Map::center};
      if (map[npyts[0]][npxt].type != MAP_TILE_TYPE_WALL &&
          map[npyts[1]][npxt].type != MAP_TILE_TYPE_WALL) {
        this->rect.x += this->speed * dt;
        this->facing = 2;
        this->state = PLAYER_SPRITE_STATE_WALK;
      }
    }
    if (IsKeyDown(KEY_W)) {
      int npxts[2] = {
          (int)floor(this->hitbox.x / Const_Map::tile_size) + Const_Map::center,
          (int)floor((this->hitbox.x + this->hitbox.width) /
                     Const_Map::tile_size) +
              Const_Map::center};
      int npyt =
          (int)floor((this->hitbox.y - this->speed * dt) / Const_Map::tile_size) +
          Const_Map::center;
      if (map[npyt][npxts[0]].type != MAP_TILE_TYPE_WALL &&
          map[npyt][npxts[1]].type != MAP_TILE_TYPE_WALL) {
        this->rect.y -= this->speed * dt;
        this->facing = 3;
        this->state = PLAYER_SPRITE_STATE_WALK;
      }
    } else if (IsKeyDown(KEY_S)) {
      int npxts[2] = {
          (int)floor(this->hitbox.x / Const_Map::tile_size) + Const_Map::center,
          (int)floor((this->hitbox.x + this->hitbox.width) /
                     Const_Map::tile_size) +
              Const_Map::center};
      int npyt =
          (int)floor((this->hitbox.y + this->hitbox.height + this->speed * dt) /
                     Const_Map::tile_size) +
          Const_Map::center;
      if (map[npyt][npxts[0]].type != MAP_TILE_TYPE_WALL &&
          map[npyt][npxts[1]].type != MAP_TILE_TYPE_WALL) {

        this->rect.y += this->speed * dt;
        this->facing = 0;
        this->state = PLAYER_SPRITE_STATE_WALK;
      }
    }

    if (std::abs((this->rect.x + this->rect.width / 2) - gamecam.target.x) >
        Const_Player::camera_follow_threshold_x) {
      if (this->rect.x > gamecam.target.x)
        gamecam.target.x =
            this->rect.x + this->rect.width / 2 - Const_Player::camera_follow_margin;
      else
        gamecam.target.x =
            this->rect.x + this->rect.width / 2 + Const_Player::camera_follow_margin;
    }
    if (std::abs((this->rect.y + this->rect.height / 2) - gamecam.target.y) >
        Const_Player::camera_follow_threshold_y) {
      if (this->rect.y > gamecam.target.y)
        gamecam.target.y = this->rect.y + this->rect.height / 2 -
                           Const_Player::camera_follow_margin *
                               Const_Player::camera_follow_y_scale;
      else
        gamecam.target.y = this->rect.y + this->rect.height / 2 +
                           Const_Player::camera_follow_margin *
                               Const_Player::camera_follow_y_scale;
    }

    this->anim_frame_real++;
    if (this->anim_frame_real == this->anim_frame_real_max) {
      this->anim_frame = (this->anim_frame + 1) % 2;
      this->anim_frame_real = 0;
    }
  }

  void draw() {
    DrawTexturePro(
        characters,
        GetPlayerSpriteSource(this->state, this->anim_frame, this->facing),
        this->rect, {0, 0}, 0.0f, WHITE);
  }
};
