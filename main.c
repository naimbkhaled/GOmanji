/**
 * @file main.c
 * @brief Point d'entrée avec gestion du menu principal.
 */

#include "header.h"

int main(int argc, char *argv[]) {
    // ===== INIT SDL =====
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) return -1;
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    SDL_Window *window = SDL_CreateWindow("Jumanji Enigme", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // ===== Fonts =====
    TTF_Font *fontQuiz = TTF_OpenFont("arial.ttf", 24);
    if(!fontQuiz) printf("Erreur police arial.ttf introuvable!\n");

    // ===== Menu Setup =====
    SDL_Texture *bg = loadTexture("bc1.jpg", renderer);
    Bouton quizBtn, puzzleBtn;
    quizBtn.normal = loadTexture("quiz1.png", renderer);
    quizBtn.hover  = loadTexture("quiz2.png", renderer);
    quizBtn.rect = (SDL_Rect){75, 250, 300, 100};

    puzzleBtn.normal = loadTexture("puzzle1.png", renderer);
    puzzleBtn.hover  = loadTexture("puzzle2.png", renderer);
    puzzleBtn.rect = (SDL_Rect){425, 250, 300, 100};

    int running = 1;
    SDL_Event e;
    int mouseX, mouseY;

    while(running) {
        SDL_GetMouseState(&mouseX, &mouseY);
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) running = 0;
            if(e.type == SDL_MOUSEBUTTONDOWN) {
                if(checkClick(quizBtn.rect, mouseX, mouseY)) {
                    jouer_quiz(renderer, fontQuiz);
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bg, NULL, NULL);
        renderButton(&quizBtn, renderer, mouseX, mouseY);
        renderButton(&puzzleBtn, renderer, mouseX, mouseY);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // ===== CLEAN =====
    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(quizBtn.normal);
    SDL_DestroyTexture(quizBtn.hover);
    SDL_DestroyTexture(puzzleBtn.normal);
    SDL_DestroyTexture(puzzleBtn.hover);
    TTF_CloseFont(fontQuiz);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
