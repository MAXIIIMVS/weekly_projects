#include "raylib.h"
#include <assert.h>
#include <math.h>
#include <time.h>

typedef struct {
  const int width;
  const int height;
  const char *title;
} WindowInfo;

typedef enum { Hour, Minute, Second } TimeType;

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

float get_radian_from_time(const struct tm *const t, TimeType type) {
  /* NOTE:
   * every circle is 360°
   * a full clock has 12 hours
   * each hour is 1/12 of a circle  :  360° / 12 = 30°
   * each minute is 1/60 of an hour :  360° / 60 = 6°
   * each second is 1/60 of a minute:  6°   / 60 = 0.1°
   */
  switch (type) {
  case Hour:
    // NOTE: tm_hour is from 0 to 23
    return deg_to_rad((t->tm_hour % 12 + t->tm_min / 60.0f) * 30.0f);
  case Minute:
    return deg_to_rad((t->tm_min + t->tm_sec / 60.0f) * 6.0f);
  case Second:
    return deg_to_rad(t->tm_sec * 6.0f);
  default:
    assert(false && "invalid type for time");
    return 0.0f;
  }
}

void draw_handle(TimeType type, const Vector2 *const start, float length,
                 const struct tm *const t, float start_angle_rad, Color color,
                 float thickness) {
  float angle = start_angle_rad + get_radian_from_time(t, type);
  float x = start->x + length * cosf(angle);
  float y = start->y + length * sinf(angle);
  DrawLineEx(*start, (Vector2){x, y}, thickness, color);
}

int main(void) {
  WindowInfo window = {.width = 300, .height = 300, .title = "Clock"};
  Vector2 circle_center = {.x = window.width / 2.0f, .y = window.height / 2.0f};
  float circle_radius = (window.height / 2.0f) - 20.0f;

  const Color BG = BEIGE;
  const Color FACE = {245, 240, 220, 255}; // warm cream

  time_t now;
  struct tm t;

  SetConfigFlags(FLAG_MSAA_4X_HINT);

  InitWindow(window.width, window.height, window.title);
  SetTargetFPS(6);

  while (!WindowShouldClose()) {
    time(&now);
    localtime_r(&now, &t);
    BeginDrawing();
    ClearBackground(BG);
    DrawCircle(circle_center.x, circle_center.y, circle_radius, FACE);

    draw_minute_marks(&circle_center, circle_radius, deg_to_rad(-90));
    draw_handle(Hour, &circle_center, circle_radius - 45.0f, &t,
                deg_to_rad(-90), RED, 5.0f);
    draw_handle(Minute, &circle_center, circle_radius - 25.0f, &t,
                deg_to_rad(-90), GREEN, 5.0f);
    draw_handle(Second, &circle_center, circle_radius - 7.0f, &t,
                deg_to_rad(-90), BLUE, 2.0f);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
