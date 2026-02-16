#include "raylib.h"
#include <math.h>

float deg_to_rad(float deg) { return deg * (PI / 180.0f); }

void draw_minute_marks(const Vector2 *const circle_center, float radius,
                       float start_angle_rad) {
  const float big_length = 6.0f;
  const float small_length = 4.0f;
  const float step = 2.0f * PI / 60.0f; // 6°

  for (int i = 0; i < 60; ++i) {
    float angle = start_angle_rad + i * step;

    float marker_length = (i % 5 == 0) ? big_length : small_length;
    float inner = radius - marker_length;

    float c = cosf(angle);
    float s = sinf(angle);

    float x1 = circle_center->x + inner * c;
    float y1 = circle_center->y + inner * s;
    float x2 = circle_center->x + radius * c;
    float y2 = circle_center->y + radius * s;

    DrawLineEx((Vector2){x1, y1}, (Vector2){x2, y2}, marker_length, DARKGRAY);
  }
}

typedef struct {
  const int width;
  const int height;
  const char *title;
} WindowInfo;

int main(void) {
  WindowInfo window = {.width = 300, .height = 300, .title = "Clock"};
  Vector2 circle_center = {.x = window.width / 2.0f, .y = window.height / 2.0f};
  float circle_radius = (window.height / 2.0f) - 20.0f;

  const Color BG = BEIGE;
  const Color FACE = {245, 240, 220, 255}; // warm cream

  // time_t now = time(NULL);
  // struct tm *t = localtime(&now);

  InitWindow(window.width, window.height, window.title);
  SetTargetFPS(60); // this is a clock, more than 60 is redundant

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BG);
    DrawCircle(circle_center.x, circle_center.y, circle_radius, FACE);
    draw_minute_marks(&circle_center, circle_radius, deg_to_rad(-90));
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
