#ifndef JOUEUR_H
#define JOUEUR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "animation.h"

typedef struct
{
    Entite anim;   

    int score;
    int vies;
    SDL_Texture *vieImg;
    
    
    int up;          
    int posinit;     // initial Y position
    
    
    float x_rel;   // position relative (x)
    float a;       // coefficient parabole
    float c;       // hauteur saut
    int dirX; 
    
    
    float energie;     
    float energieMax;   
    
    


} Joueur;

void initialiserJoueur(Joueur *j, SDL_Renderer *renderer, char image[]);
void initialiserJoueur1(Joueur *j, SDL_Renderer *renderer, char image[]);
void initialiserJoueur2(Joueur *j, SDL_Renderer *renderer, char image[]);
void afficherJoueur(Joueur j, SDL_Renderer *renderer);
void animerJoueur(Joueur *j, int largeurSprite);
void deplacerJoueur(Joueur *j, SDL_Event event);
void deplacerJoueur1(Joueur *j, SDL_Event event);
void deplacerJoueur2(Joueur *j, SDL_Event event);
void saut(Joueur *j, int dt);
void saut1(Joueur *j, int dt);
void saut2(Joueur *j, int dt);
void afficherVies(Joueur j, SDL_Renderer *renderer);
void afficherVies1(Joueur j, SDL_Renderer *renderer);
void afficherVies2(Joueur j, SDL_Renderer *renderer);
void attaquer(Joueur *j);
void afficherEnergie(Joueur j, SDL_Renderer *renderer);
#endif
