#include <SDL2/SDL.h>
#include <stdbool.h>
#include <string.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("c_playground", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }

    /*
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return 1;
    }
    */

    SDL_Surface * window_surface = SDL_GetWindowSurface(window);
    if (window_surface == NULL) {
      printf("SDL_GetWindowSurface Error: %s\n", SDL_GetError());
      return 1;
    }

    SDL_Surface * image_surface1 = SDL_LoadBMP("test.bmp");
    if (image_surface1 == NULL) {
      printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
      return 1;
    }

    SDL_Surface * image_surface2 = SDL_LoadBMP("test2.bmp");
    if (image_surface2 == NULL) {
      printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
      return 1;
    }
    SDL_Surface * image_surface3 = SDL_LoadBMP("test3.bmp");
    if (image_surface3 == NULL) {
      printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
      return 1;
    }

    SDL_Surface * current_image = image_surface1;

    /*
    SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    */

    bool is_running = true;
    SDL_Event event;

    while (is_running) {   //Gameloop

      while (SDL_PollEvent(&event)) {   //Eventloop (something happens->event queue->SDL_Pollevent processes these)
        switch (event.type) {

          case SDL_QUIT:
            is_running = false;
            break;

          case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
              case SDLK_1:
                current_image = image_surface1;
                break;
              case SDLK_2:
                current_image = image_surface2;
                break;
              case SDLK_3:
                current_image = image_surface3;
                break;
              default:
                break;
            }

          case SDL_MOUSEBUTTONDOWN:
            switch(event.button.button) {
              case SDL_BUTTON_LEFT:
                if (event.button.clicks == 2) {
                  current_image = image_surface3;
                  break;
                }
                current_image = image_surface1;
                break;
              case SDL_BUTTON_RIGHT:
                current_image = image_surface2;
                break;
              default:
                break;
            }

          default:
            break;
        }
      }
      SDL_BlitSurface(current_image, NULL, window_surface, NULL);
      SDL_UpdateWindowSurface(window);
    }

    SDL_FreeSurface(image_surface1);
    SDL_FreeSurface(image_surface2);
    SDL_FreeSurface(image_surface3);

    current_image = image_surface1 = image_surface2 = image_surface3 = NULL;
    SDL_Quit();

    return 0;
}
