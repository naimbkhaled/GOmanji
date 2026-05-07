#ifndef HEADER_H
#define HEADER_H

/**
 * @file header.h
 * @brief Déclarations des structures et fonctions du jeu SDL2.
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

#define FIXE 0
#define MOBILE 1
#define DESTRUCTIBLE 2

/**
 * @struct Plateforme
 * @brief Structure d'une plateforme.
 */
typedef struct
{
    SDL_Rect rect;
    SDL_Texture *texture;
    int type;
    int dir;
    int speed;
    int alive;

} Plateforme;

/**
 * @struct ListePlateformes
 * @brief Liste des plateformes.
 */
typedef struct
{
    Plateforme p[10];
    int nb;

} ListePlateformes;

/**
 * @struct Timer
 * @brief Structure du timer.
 */
typedef struct
{
    Uint32 startTicks;

} Timer;

/**
 * @struct Guide
 * @brief Structure des guides affichés.
 */
typedef struct
{
    SDL_Texture *texture;
    int active;
    Uint32 startTime;

} Guide;

/**
 * @struct Segment
 * @brief Structure contenant un background.
 */
typedef struct
{
    SDL_Texture *background;

} Segment;

/**
 * @struct Game
 * @brief Structure principale du jeu.
 */
typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;

    SDL_Rect camera;
    SDL_Rect cameraRight;

    Segment segments[3];

    int currentBG;
    int level;
    int multi;

    ListePlateformes plateformes;

    Timer timer;

    Guide guide;
    Guide levelGuide;

} Game;


/* Plateformes */
void initPlateformes(ListePlateformes *lp, SDL_Renderer *r, int level);
void updatePlateformes(ListePlateformes *lp);
void renderPlateformes(ListePlateformes *lp, SDL_Renderer *r, int camX);
void destroyPlateformes(ListePlateformes *lp);

/* Timer */
void initTimer(Timer *t);
void renderTimer(Timer *t, SDL_Renderer *renderer, TTF_Font *font);

/* Guide */
void initGuide(Guide *g, SDL_Renderer *renderer, const char *path);
void showGuide(Guide *g, int timed);
void updateGuide(Guide *g);
void renderGuide(Guide *g, SDL_Renderer *renderer);

/* Jeu */
int initGame(Game *g);
void handleInput(Game *g, int *running);
void updateGame(Game *g);
void renderGame(Game *g);
void cleanGame(Game *g);

#endif
