#include <cmath>
#include <raylib.h>

#define RENDER_W 800
#define RENDER_H 600

void DrawTextCentered(const char *text, int x, int y, int fontSize,
                      Color color) {
  DrawText(text, x - (MeasureText(text, fontSize) / 2), y, fontSize, color);
}

enum GameMenuState { GMSTATE_MAIN, GMSTATE_GAME, GMSTATE_SHOP, GMSTATE_DEATH };

int main() {
  InitWindow(RENDER_W, RENDER_H, "Capitalism");
  SetWindowState(FLAG_FULLSCREEN_MODE);

  enum GameMenuState game_menu_state = GMSTATE_MAIN;

  RenderTexture2D render_texture = LoadRenderTexture(RENDER_W, RENDER_H);
  Texture2D gh_logo = LoadTexture("assets/github.jpg");

  while (!WindowShouldClose()) {
    ClearBackground(WHITE);
    BeginTextureMode(render_texture);
    DrawRectangle(0, 0, 800, 600, BLACK);

    if (game_menu_state == GMSTATE_MAIN) {
      DrawTexture(gh_logo, 0, 0, WHITE);
      DrawTextCentered("game title", RENDER_W / 2, RENDER_H / 3, 64, GREEN);
    }

    EndTextureMode();

    BeginDrawing();

    // draw render texture
    int rw = GetRenderWidth();
    int rh = GetRenderHeight();
    float scale = fminf((float)rw / RENDER_W, (float)rh / RENDER_H);
    int fw = (int)(RENDER_W * scale);
    int fh = (int)(RENDER_H * scale);
    int ox = (rw - fw) / 2;
    int oy = (rh - fh) / 2;
    DrawTexturePro(render_texture.texture, {0, 0, RENDER_W, -RENDER_H},
                   {(float)ox, (float)oy, (float)fw, (float)fh}, {0, 0}, 0,
                   WHITE);

    EndDrawing();
  }
  CloseWindow();
  return 0;
}
