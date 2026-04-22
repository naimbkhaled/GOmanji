#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL.h>

typedef struct {

    SDL_Rect rect;
    const char* imagePath;
    SDL_Texture* texture;

} Background;

void initBackground(Background* bg, SDL_Renderer* renderer);
void renderBackground(SDL_Renderer* renderer, Background* bg);
void freeBackground(Background* bg);

#endif
