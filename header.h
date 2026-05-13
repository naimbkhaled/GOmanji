/**
 * @file header.h
 * @brief Définition des structures et prototypes pour le menu et le quiz Jumanji.
 */

#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/* --- Structures --- */

/** @struct Enigme représentant une question du quiz */
typedef struct {
    char question[256];/**< Texte de la question */
    char choix1[100];/**< Option 1 */
    char choix2[100];/**< Option 2 */
    char choix3[100];/**< Option 3 */
    int bonne_reponse;/**< Indice de la réponse correcte */
    int deja_pose;/**< Pour éviter la répétition */
} Enigme;
/** @struct Bouton pour le menu */
typedef struct {
    SDL_Texture *normal;
    SDL_Texture *hover;
    SDL_Rect rect;
} Bouton;

typedef struct {
    SDL_Texture *zone;
    Mix_Music *suspenseMusic;
} Quiz;
/* --- Prototypes --- */
SDL_Texture* loadTexture(const char *file, SDL_Renderer *renderer);
int checkClick(SDL_Rect rect, int mouseX, int mouseY);
void renderButton(Bouton *b, SDL_Renderer *renderer, int mouseX, int mouseY);
int chargerEnigmes(Enigme T[], int *n);/** @brief Charge les énigmes depuis le fichier texte */
int choisirEnigme(Enigme T[], int n);/** @brief Sélectionne une énigme aléatoire */
void jouer_quiz(SDL_Renderer *renderer, TTF_Font *fontQuiz);/** @brief Gère la boucle complète du quiz  */

#endif
