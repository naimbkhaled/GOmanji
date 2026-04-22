#include "animation.h"
#include <stdio.h>

// ================= SPRITE SHEET =================

void initialiserEntiteSprite(Entite *e, SDL_Renderer *renderer, char image[])
{
    e->mode = 1;
    e->direction = 0;

    SDL_Surface *surface = IMG_Load(image);
    e->sprite = SDL_CreateTextureFromSurface(renderer, surface);

    int largeur = surface->w;
    int hauteur = surface->h;

    SDL_FreeSurface(surface);

    e->nbL = 2;
    e->nbC = 4;

    e->posEcran.x = 0;
    e->posEcran.y = 250;
    e->posEcran.w = largeur / e->nbC;
    e->posEcran.h = hauteur / e->nbL;

    e->posSprite.x = 0;
    e->posSprite.y = 0;
    e->posSprite.w = largeur / e->nbC;
    e->posSprite.h = hauteur / e->nbL;
}


void initialiserEntiteSprite1(Entite *e, SDL_Renderer *renderer, char image[])
{
    e->mode = 1;
    e->direction = 0;

    SDL_Surface *surface = IMG_Load(image);
    e->sprite = SDL_CreateTextureFromSurface(renderer, surface);

    int largeur = surface->w;
    int hauteur = surface->h;

    SDL_FreeSurface(surface);

    e->nbL = 2;
    e->nbC = 4;

    e->posEcran.x = 0;
    e->posEcran.y = 400;
    e->posEcran.w = largeur / e->nbC;
    e->posEcran.h = hauteur / e->nbL;

    e->posSprite.x = 0;
    e->posSprite.y = 0;
    e->posSprite.w = largeur / e->nbC;
    e->posSprite.h = hauteur / e->nbL;
}



void initialiserEntiteSprite2(Entite *e, SDL_Renderer *renderer, char image[])
{
    e->mode = 1;
    e->direction = 0;

    SDL_Surface *surface = IMG_Load(image);
    e->sprite = SDL_CreateTextureFromSurface(renderer, surface);

    int largeur = surface->w;
    int hauteur = surface->h;

    SDL_FreeSurface(surface);

    e->nbL = 2;
    e->nbC = 4;

    e->posEcran.x = 400;
    e->posEcran.y = 400;
    e->posEcran.w = largeur / e->nbC;
    e->posEcran.h = hauteur / e->nbL;

    e->posSprite.x = 0;
    e->posSprite.y = 0;
    e->posSprite.w = largeur / e->nbC;
    e->posSprite.h = hauteur / e->nbL;
}


void animerEntiteSprite(Entite *e, int largeurSprite)
{
    e->posSprite.y = e->direction * e->posSprite.h;

    if (e->posSprite.x == largeurSprite - e->posSprite.w)
        e->posSprite.x = 0;
    else
        e->posSprite.x += e->posSprite.w;
}

// ================= IMAGES SEPAREES =================

void initialiserEntiteImages(Entite *e, SDL_Renderer *renderer)
{
    e->mode = 2;

    e->direction = 0;
    e->num = 0;

    e->n = 10;
    e->m = 10;

    char chemin[50];

    for (int i = 0; i < e->n; i++)
    {
        sprintf(chemin, "droite_%d.png", i);
        SDL_Surface *s = IMG_Load(chemin);
        e->tab[i] = SDL_CreateTextureFromSurface(renderer, s);
        SDL_FreeSurface(s);
    }

    for (int i = 0; i < e->m; i++)
    {
        sprintf(chemin, "gauche_%d.png", i);
        SDL_Surface *s = IMG_Load(chemin);
        e->tab[e->n + i] = SDL_CreateTextureFromSurface(renderer, s);
        SDL_FreeSurface(s);
    }

    e->posEcran.x = 100;
    e->posEcran.y = 100;
    e->posEcran.w = 100;
    e->posEcran.h = 100;
}

void animerEntiteImages(Entite *e)
{
    if (e->direction == 0)
    {
        if (e->num == e->n - 1)
            e->num = 0;
        else
            e->num++;
    }
    else
    {
        if (e->num == e->n + e->m - 1)
            e->num = e->n;
        else
            e->num++;
    }
}
// ================= AFFICHAGE =================

void afficherEntite(Entite e, SDL_Renderer *renderer)
{
    if (e.mode == 1)
        SDL_RenderCopy(renderer, e.sprite, &e.posSprite, &e.posEcran);
    else
        SDL_RenderCopy(renderer, e.tab[e.num], NULL, &e.posEcran);
}

// ================= LIBERATION =================

void libererEntite(Entite *e)
{
    if (e->mode == 1)
    {
        SDL_DestroyTexture(e->sprite);
    }
    else
    {
        for (int i = 0; i < e->n + e->m; i++)
            SDL_DestroyTexture(e->tab[i]);
    }
}
