#include "SDL3/SDL_events.h"
#include <SDL3/SDL.h>

struct App {
  bool is_running{false};
  SDL_Window *window{nullptr};
  SDL_Renderer *renderer{nullptr};
};

int main() {
  App app{};
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
    return 1;
  }
  app.window = SDL_CreateWindow("Star Field", 800, 800, 0);
  if (!app.window) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    SDL_Quit();
    return 1;
  }
  app.renderer = SDL_CreateRenderer(app.window, nullptr);
  if (!app.renderer) {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    SDL_DestroyWindow(app.window);
    SDL_Quit();
    return 1;
  }

  SDL_Event e{};
  app.is_running = true;

  while (app.is_running) {
    // 1. Handle events
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_EVENT_QUIT ||
          (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE)) {
        app.is_running = false;
      }
    }

    // TODO: Add delta time and reduce CPU usage

    // TODO: handle these
    // 2. Update game state
    // update_stars();
    // 3. Render the frame
    // SDL_RenderClear(app.renderer);
    // render_stars(app.renderer);
    // SDL_RenderPresent(app.renderer);
  }

  SDL_DestroyRenderer(app.renderer);
  SDL_DestroyWindow(app.window);
  SDL_Quit();

  return 0;
}
