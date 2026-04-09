#pragma once
#include "global.hpp"

#include "raylib.h"
#include "utils.hpp"

class GameMenuMain {
public:
  const Texture2D gh_logo = LoadTexture("assets/github.jpg");
  bool is_switching_to_game = false;
  SceneTransitionFade transition =
      SceneTransitionFade(16, ColorAlpha(DARKGREEN, 0), DARKGREEN);
  float play_text_hovered_time = 0;
  float quit_text_hovered_time = 0;
  bool play_text_hovered, quit_text_hovered;
  const Rectangle play_text_box = {RENDER_W / 2 - 100, RENDER_H / 3 + 64 + 8,
                                   200, 48 + 16};
  const Rectangle quit_text_box = {
      RENDER_W / 2 - 100, RENDER_H / 3 + 64 + 16 + 48 + 8, 200, 48 + 12};

  void draw(Vector2 mouse_pos) {
    DrawTexture(gh_logo, 0, 0, WHITE);
    DrawTextCentered("game title", RENDER_W / 2, RENDER_H / 3, 64, GREEN);
    play_text_hovered = mouse_pos.x > play_text_box.x &&
                        mouse_pos.x < play_text_box.x + play_text_box.width &&
                        mouse_pos.y > play_text_box.y &&
                        mouse_pos.y < play_text_box.y + play_text_box.height;
    if (play_text_hovered && play_text_hovered_time < 30)
      play_text_hovered_time++;
    else if (!play_text_hovered && play_text_hovered_time > 0)
      play_text_hovered_time--;
    quit_text_hovered = mouse_pos.x > quit_text_box.x &&
                        mouse_pos.x < quit_text_box.x + quit_text_box.width &&
                        mouse_pos.y > quit_text_box.y &&
                        mouse_pos.y < quit_text_box.y + quit_text_box.height;
    if (quit_text_hovered && quit_text_hovered_time < 30)
      quit_text_hovered_time++;
    else if (!quit_text_hovered && quit_text_hovered_time > 0)
      quit_text_hovered_time--;
    float play_text_x_offset =
        12 * ease_in_out_cubic(play_text_hovered_time / 30.0f);
    float quit_text_x_offset =
        12 * ease_in_out_cubic(quit_text_hovered_time / 30.0f);
    DrawTextCentered("> play", RENDER_W / 2 + play_text_x_offset,
                     RENDER_H / 3 + 64 + 16, 48, WHITE);
    DrawTextCentered("> quit", RENDER_W / 2 + quit_text_x_offset,
                     RENDER_H / 3 + 64 + 16 + 48 + 8, 48, WHITE);
    if (is_switching_to_game) {
      DrawRectangle(0, 0, RENDER_W, RENDER_H, transition.getColor());
    }
  }

  void update(Vector2 mouse_pos, GameMenuState &state) {
    if (is_switching_to_game) {
      transition.update();
      if (transition.finished) {
        state = GMSTATE_GAME;
      }
      return;
    }
    if (quit_text_hovered && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      exitGame = true;
    }
    if (play_text_hovered && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      is_switching_to_game = true;
    }
  }
};
