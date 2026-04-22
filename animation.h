#ifndef ENTITE_H
#define ENTITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



typedef struct
{
   
    int direction;
    SDL_Rect posEcran;


    SDL_Texture *sprite;
    SDL_Rect posSprite;
    int nbL;
    int nbC;


    SDL_Texture *tab[20];
    int num;
    int n; 
    int m; 

    int mode; 

} Entite;


void initialiserEntiteSprite(Entite *e, SDL_Renderer *renderer, char image[]);
void initialiserEntiteSprite1(Entite *e, SDL_Renderer *renderer, char image[]);
void initialiserEntiteSprite2(Entite *e, SDL_Renderer *renderer, char image[]);
void animerEntiteSprite(Entite *e, int largeurSprite);

void initialiserEntiteImages(Entite *e, SDL_Renderer *renderer);
void animerEntiteImages(Entite *e);

void afficherEntite(Entite e, SDL_Renderer *renderer);
void libererEntite(Entite *e);

#endif
