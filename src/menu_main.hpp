#pragma once
#include "global.hpp"

#include "raylib.h"
#include "utils.hpp"
#include <algorithm>
#include <cstring>
#include <string>

class GameMenuMain {
public:
  const Texture2D gh_logo = LoadTexture("assets/github.jpg");
  bool is_switching_to_game = false;
  SceneTransitionFade transition =
      SceneTransitionFade(16, ColorAlpha(DARKGREEN, 0), DARKGREEN);
  float play_text_hovered_time = 0;
  float quit_text_hovered_time = 0;
  bool play_text_hovered, quit_text_hovered;
  int frame = 1;
  const Rectangle play_text_box = {Const_Render::width / 2 - 100,
                                   Const_Render::height / 3 + 64 + 8, 200,
                                   48 + 16};
  const Rectangle quit_text_box = {
      Const_Render::width / 2 - 100,
      Const_Render::height / 3 + 64 + 16 + 48 + 8, 200, 48 + 12};

  void draw_title(std::string title) {
    int title_center_x = Const_Render::width / 2;
    int title_center_y = Const_Render::height / 3;
    const int font_size = 64;
    const int title_len = title.length();

    int title_left_x =
        Const_Render::width / 2 -
        (MeasureText(title.c_str(), 64) + (title_len * 5)) / 2.0f;

    for (int i = 0; i < title_len; i++) {
      char c[2] = {title[i], '\0'};

      int cycle_length = 120;
      int local_frame = (1000 + frame - (i * 4)) % cycle_length;

      int p = abs((local_frame % cycle_length) - (cycle_length / 2));

      int half_cycle = cycle_length / 2;
      int pause_frames = 2;
      float t = 0.0f;

      if (p <= pause_frames) {
        t = 0.0f;
      } else if (p >= (half_cycle - pause_frames)) {
        t = 1.0f;
      } else {
        t = (float)(p - pause_frames) / (half_cycle - 2 * pause_frames);
      }

      float animation_offset = ease_in_out_quadratic(t) * 32 - 16;

      DrawText(c,
               (5 * i) + title_left_x +
                   MeasureText(title.substr(0, i).c_str(), font_size),
               title_center_y + (int)animation_offset, font_size, YELLOW);
    }
  }

  void draw(Vector2 mouse_pos) {
    DrawTexture(gh_logo, 0, 0, WHITE);
    draw_title("gold, gold, gold");
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
    DrawTextCentered("> play", Const_Render::width / 2 + play_text_x_offset,
                     Const_Render::height / 3 + 64 + 16, 48, WHITE);
    DrawTextCentered("> quit", Const_Render::width / 2 + quit_text_x_offset,
                     Const_Render::height / 3 + 64 + 16 + 48 + 8, 48, WHITE);
    if (is_switching_to_game) {
      DrawRectangle(0, 0, Const_Render::width, Const_Render::height,
                    transition.getColor());
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

    frame++;
    // note: it takes 1.4 years for frame to underflow
  }
};
