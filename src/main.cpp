#include "game.hpp"
#include "global.hpp"
#include "menu_main.hpp"
#include <cmath>
#include <raylib.h>

Texture2D tileset_01;
Texture2D tileset_02;
Texture2D tileset_04;
Texture2D tileset_05;
Texture2D tileset_b;
Texture2D characters;

int main() {
  InitWindow(Const_Render::width, Const_Render::height, "Capitalism");
  LoadAssets();
  // SetWindowState(FLAG_FULLSCREEN_MODE);
  SetWindowState(FLAG_WINDOW_RESIZABLE);

  enum GameMenuState game_menu_state = GMSTATE_GAME;

  RenderTexture2D render_texture =
      LoadRenderTexture(Const_Render::width, Const_Render::height);
  GameMenuMain main_menu;
  Game game;

  SetTargetFPS(Const_Render::target_fps);

  while (!WindowShouldClose() && !exitGame) {
    DrawFPS(0, 0);
    // for render texture
    int rw = GetScreenWidth();
    int rh = GetScreenHeight();
    float scale =
        fminf((float)rw / Const_Render::width, (float)rh / Const_Render::height);
    int fw = (int)(Const_Render::width * scale);
    int fh = (int)(Const_Render::height * scale);
    int ox = (rw - fw) / 2;
    int oy = (rh - fh) / 2;
    //-----
    Vector2 mouse_pos = GetMousePosition();
    mouse_pos.x = (mouse_pos.x - ox) / scale;
    mouse_pos.y = (mouse_pos.y - oy) / scale;

    float dt = GetFrameTime();

    switch (game_menu_state) {
    case GMSTATE_MAIN: {
      main_menu.update(mouse_pos, game_menu_state);
      break;
    }
    case GMSTATE_GAME: {
      game.update(dt);
      break;
    }
    };

    ClearBackground(WHITE);
    BeginTextureMode(render_texture);
    DrawRectangle(0, 0, Const_Render::width, Const_Render::height, BLACK);

    if (game_menu_state == GMSTATE_MAIN) {
      main_menu.draw(mouse_pos);
    } else if (game_menu_state == GMSTATE_GAME) {
      game.draw();
    }

   EndTextureMode();

    BeginDrawing();

    // draw render texture

    DrawTexturePro(render_texture.texture,
                   {0, 0, Const_Render::width, -Const_Render::height},
                   {(float)ox, (float)oy, (float)fw, (float)fh}, {0, 0}, 0,
                   WHITE);

    EndDrawing();
  }
  CloseWindow();
  return 0;
}
