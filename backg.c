#include "backg.h"
#include <SDL2/SDL_image.h>

void initBackground(Background* bg, SDL_Renderer* renderer)
{
    bg->texture = IMG_LoadTexture(renderer, bg->imagePath);
}

void renderBackground(SDL_Renderer* renderer, Background* bg)
{
    SDL_RenderCopy(renderer, bg->texture, NULL, &bg->rect);
}

void freeBackground(Background* bg)
{
    SDL_DestroyTexture(bg->texture);
}
