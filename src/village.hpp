#pragma once
#include "global.hpp"
#include "raylib.h"
#include "utils.hpp"

enum GameMenuVillageState { VILLAGE_STATE_SELECTING };

struct GameMenuVillageSelectionOption {
  const char *text;
  int hover = 0;
  GameMenuVillageSelectionOption(const char *text) : text(text) {}
};

class GameMenuVillage {
public:
  GameMenuVillageState state = VILLAGE_STATE_SELECTING;

  GameMenuVillageSelectionOption selections[Const_Village::selection_count] = {
      GameMenuVillageSelectionOption("> Inn"),
      GameMenuVillageSelectionOption("> Notice Board"),
      GameMenuVillageSelectionOption("> Bank"),
      GameMenuVillageSelectionOption("> Blacksmith"),
      GameMenuVillageSelectionOption("> gas station :3"),
      GameMenuVillageSelectionOption("> Alchemist"),
      GameMenuVillageSelectionOption("> Armorsmith")};

  void draw() {
    switch (state) {
    case VILLAGE_STATE_SELECTING: {
      DrawText("Village",
               Const_Render::width -
                   MeasureText("Village", Const_Village::title_font_size) -
                   Const_Village::title_margin,
               Const_Village::title_margin, Const_Village::title_font_size,
               WHITE);
      for (int i = 0; i < Const_Village::selection_count; i++) {
        GameMenuVillageSelectionOption opt = selections[i];
        DrawText(opt.text,
                 Const_Village::title_margin +
                     Const_Village::option_hover_offset_px *
                         ease_in_out_quadratic(opt.hover /
                                               Const_Village::option_hover_divisor),
                 Const_Village::option_start_y + i * Const_Village::option_gap_y,
                 Const_Village::option_font_size, WHITE);
      }

      break;
    }
    }
  }
  void update(float dt, Vector2 mouse_pos) {
    for (int i = 0; i < Const_Village::selection_count; i++) {
      GameMenuVillageSelectionOption &opt = selections[i];
      Rectangle hover_rect = {0,
                              (float)Const_Village::option_start_y +
                                  i * Const_Village::option_gap_y -
                                  Const_Village::option_gap_y / 4.0f,
                              Const_Village::option_hover_rect_width,
                              Const_Village::option_gap_y *
                                  Const_Village::option_hover_rect_height_scale};
      if (mouse_pos.x > hover_rect.x &&
          mouse_pos.x < hover_rect.x + hover_rect.width &&
          mouse_pos.y > hover_rect.y &&
          mouse_pos.y < hover_rect.y + hover_rect.height) {
        opt.hover++;
        if (opt.hover > Const_Village::option_hover_max)
          opt.hover = Const_Village::option_hover_max;
      } else if (opt.hover > 0)
        opt.hover--;
    }
  }
};
