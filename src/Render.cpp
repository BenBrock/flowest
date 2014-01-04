#include <SDL2/SDL.h>
#include "Surface.h"

int main(int argc, char **argv)
{
  SDL_Init(SDL_INIT_VIDEO);

  const char *title = "flowist";
  int width = 600;
  int height = 400;

  SDL_Window *window = SDL_CreateWindow(title,
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    width, height, SDL_WINDOW_RESIZABLE);

  Uint32 renderer_flags = SDL_RENDERER_ACCELERATED |
    SDL_RENDERER_PRESENTVSYNC;
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, renderer_flags);

  SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_STREAMING, width, height);

  while (1) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        break;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Write to texture
    Uint32 *pixels;
    int pitch;

    int err = SDL_LockTexture(texture, NULL, (void **) &pixels, &pitch);

    for (int i = 0; i < width * height; i++) {
      pixels[i] = 0x0;
    }

    SDL_UnlockTexture(texture);

    // Done writing to texture

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }

  SDL_Quit();
  return 0;
}
