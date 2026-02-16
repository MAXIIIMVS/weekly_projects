#include "raylib.h"
#include <stdio.h>
#include <time.h>

typedef struct {
  const int width;
  const int height;
  const char *title;
} WindowInfo;

int main(void) {
  WindowInfo window = {.width = 300, .height = 300, .title = "Clock"};

  const Color BG = {18, 32, 47, 255};      // deep navy
  const Color FACE = {245, 240, 220, 255}; // warm cream

  // time_t now = time(NULL);
  // struct tm *t = localtime(&now);

  InitWindow(window.width, window.height, window.title);
  SetTargetFPS(60); // this is a clock, more than 60 is redundant

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BG);
    DrawCircle(window.width / 2, window.height / 2,
               (window.height / 2.0f) - 20.0f, FACE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
