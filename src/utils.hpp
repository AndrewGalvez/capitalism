#pragma once
#include "global.hpp"
#include <cmath>
#include <raylib.h>

inline float ease_in_out_quadratic(float t) {
  return t < 0.5 ? 2 * t * t : 1 - std::pow(-2 * t + 2, 2) / 2;
}

inline float ease_in_out_cubic(float t) {
  return t < 0.5 ? 4 * t * t * t : 1 - std::pow(-2 * t + 2, 3) / 2;
}

void DrawTextCentered(const char *text, int x, int y, int fontSize,
                      Color color) {
  DrawText(text, x - (MeasureText(text, fontSize) / 2), y, fontSize, color);
}

class SceneTransitionFade {
public:
  int frames = 0;
  int maxFrames = 0;
  Color start, end;
  bool finished = false;

  void update() {
    if (finished)
      return;
    frames++;
    if (maxFrames == frames) {
      finished = true;
    }
  }

  SceneTransitionFade(int maxFrames, Color start, Color end)
      : maxFrames(maxFrames), start(start), end(end) {};

  Color getColor() {
    return ColorLerp(start, end,
                     ease_in_out_cubic((float)frames / (float)maxFrames));
  }
};
