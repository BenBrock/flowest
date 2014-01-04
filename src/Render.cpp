#include <SDL2/SDL.h>
#include "Surface.h"
#include "Render.h"

void shadow(Surface *surface, SDL_Texture *texture);

void display_window(Surface *surface){
  SDL_Init(SDL_INIT_VIDEO);

  const char *title = "flowest";
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
    shadow(surface, texture);

    // Done writing to texture

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }

  SDL_Quit();
}



void shadow(Surface *surface, SDL_Texture *texture){
    Uint32 *pixels;
    int pitch;
    int width;
    int height;

    SDL_QueryTexture(texture, NULL,NULL,
                      &width, &height);

    int err = SDL_LockTexture(texture, NULL, (void **) &pixels, &pitch);

    for (int i = 0; i < width * height; i++){
      pixels[i] = 0x000000FF;
    }

    for (int i = 0; i < surface->voxels.size(); i++){
      int scr_x = surface->voxels[i]->position.x; //Screen x
      int scr_y = surface->voxels[i]->position.z; //Screen y

      scr_x = scr_x + width/2;
      scr_y = scr_y + height/2;

      pixels[scr_x + width * scr_y] = 0xFFFFFFFF;
    }

    SDL_UnlockTexture(texture);
}
