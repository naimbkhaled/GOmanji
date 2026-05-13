/**
 * @file source.c
 * @brief Implémentation des fonctions de gestion des énigmes et utilitaires.
 * @author Ayoub Aroua
 */

#include "header.h"

/**
 * @brief Fonction principale qui gère le cycle de vie du quiz.
 * @details Cette fonction gère l'affichage, la logique des questions, le score et le temps.
 * @param renderer Le moteur de rendu SDL utilisé pour le dessin.
 * @param fontQuiz La police de caractères utilisée pour le texte.
 */
void jouer_quiz(SDL_Renderer *renderer, TTF_Font *fontQuiz) {
    
    /** @name Ressources_Graphiques
     *  Textures pour le background, les vies et les écrans de fin.
     */
    /**@{*/
    SDL_Texture *background = IMG_LoadTexture(renderer, "background.bmp");
    SDL_Texture *heart = IMG_LoadTexture(renderer, "heart.bmp");
    SDL_Texture *gameover = IMG_LoadTexture(renderer, "gameover.bmp");
    SDL_Texture *win = IMG_LoadTexture(renderer, "win.bmp");
    /**@}*/

    /** @name Ressources_Audio
     *  Effets sonores pour les réponses et la victoire.
     */
    /**@{*/
    Mix_Chunk *soundTrue = Mix_LoadWAV("true.wav");
    Mix_Chunk *soundFalse = Mix_LoadWAV("false.wav");
    Mix_Chunk *winSound = Mix_LoadWAV("winner.wav");

    if (!win) printf("ERROR win.png\n");
    if (!winSound) printf("ERROR winner.wav\n");
    /**@}*/

    Mix_Volume(-1, MIX_MAX_VOLUME);
    Mix_VolumeMusic(MIX_MAX_VOLUME);

    TTF_Font *font = TTF_OpenFont("DejaVuSans.ttf", 28);
    if(!font) font = fontQuiz; 

    SDL_Color white = {255,255,255};
    SDL_Color gold = {255,215,0};
    SDL_Color blue = {100,180,255};
    SDL_Color red = {255,80,80};

    /** @name Logique_Quiz
     *  Chargement des énigmes et initialisation du tirage au sort.
     */
    /**@{*/
    Enigme T[20];
    int n = 0;
    chargerEnigmes(T, &n);

    srand(time(NULL));
    int current = choisirEnigme(T, n);
    /**@}*/

    int score = 0, level = 1, vie = 3;
    int questionsRepondues = 0;
    Uint32 startTime = SDL_GetTicks();
    int temps = 10;
    SDL_Event e;
    int running = 1;

    SDL_Rect btn1 = {200,240,600,60};
    SDL_Rect btn2 = {200,310,600,60};
    SDL_Rect btn3 = {200,380,600,60};

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) { running = 0; exit(0); }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int x = e.button.x;
                int y = e.button.y;
                int rep = 0;

                if (SDL_PointInRect(&(SDL_Point){x,y}, &btn1)) rep = 1;
                if (SDL_PointInRect(&(SDL_Point){x,y}, &btn2)) rep = 2;
                if (SDL_PointInRect(&(SDL_Point){x,y}, &btn3)) rep = 3;

                if (rep != 0)
                {
                    questionsRepondues++; 
                    if (rep == T[current].bonne_reponse)
                    {
                        score += 100;
                        level++;
                        Mix_PlayChannel(-1, soundTrue, 0);
                    }
                    else
                    {
                        vie--;
                        Mix_PlayChannel(-1, soundFalse, 0);
                    }
                    current = choisirEnigme(T, n);
                    startTime = SDL_GetTicks();
                }
            }
        }

        int elapsed = (SDL_GetTicks() - startTime) / 1000;
        int remaining = temps - elapsed;

        if (remaining <= 0)
        {
            vie--;
            questionsRepondues++; 
            current = choisirEnigme(T, n);
            startTime = SDL_GetTicks();
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0,0,0,120);
        SDL_RenderFillRect(renderer, &(SDL_Rect){10,10,230,110});

        /** @name Affichage_UI
         *  Mise à jour des textes de score, niveau et chrono.
         */
        /**@{*/
        char s[100];
        sprintf(s, "SCORE %04d", score);
        SDL_Surface *surf = TTF_RenderText_Blended(font, s, gold);
        SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_RenderCopy(renderer, tex, NULL, &(SDL_Rect){20,20,surf->w,surf->h});
        SDL_FreeSurface(surf); SDL_DestroyTexture(tex);

        sprintf(s, "LEVEL %02d", level);
        surf = TTF_RenderText_Blended(font, s, blue);
        tex = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_RenderCopy(renderer, tex, NULL, &(SDL_Rect){20,60,surf->w,surf->h});
        SDL_FreeSurface(surf); SDL_DestroyTexture(tex);

        if (remaining < 0) remaining = 0;
        sprintf(s, "TIME %02d", remaining);
        SDL_Color tcolor = (remaining <= 3) ? red : white;
        surf = TTF_RenderText_Blended(font, s, tcolor);
        tex = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_RenderCopy(renderer, tex, NULL, &(SDL_Rect){450,20,surf->w,surf->h});
        SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
        /**@}*/

        surf = TTF_RenderText_Blended(font, T[current].question, white);
        tex = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_RenderCopy(renderer, tex, NULL, &(SDL_Rect){390,170,surf->w,surf->h});
        SDL_FreeSurface(surf); SDL_DestroyTexture(tex);

        char *choix[3] = {T[current].choix1, T[current].choix2, T[current].choix3};
        SDL_Rect btns[3] = {btn1, btn2, btn3};

        for(int i=0;i<3;i++)
        {
            surf = TTF_RenderText_Blended(font, choix[i], white);
            tex = SDL_CreateTextureFromSurface(renderer, surf);
            SDL_Rect r = { btns[i].x + (btns[i].w - surf->w)/2, btns[i].y + (btns[i].h - surf->h)/2, surf->w, surf->h };
            SDL_RenderCopy(renderer, tex, NULL, &r);
            SDL_FreeSurface(surf);
            SDL_DestroyTexture(tex);
        }

        for(int i=0;i<vie;i++)
        {
            SDL_RenderCopy(renderer, heart, NULL, &(SDL_Rect){850+i*40,20,30,30});
        }

        if (questionsRepondues >= 9 && vie > 0)
        {
            Mix_HaltChannel(-1);
            Mix_PlayChannel(-1, winSound, 0);
            SDL_SetRenderDrawColor(renderer,0,0,0,200);
            SDL_RenderFillRect(renderer,&(SDL_Rect){0,0,1000,600});
            SDL_RenderCopy(renderer, win, NULL, &(SDL_Rect){150,50,700,500});
            SDL_RenderPresent(renderer);
            SDL_Delay(3000);
            running = 0;
        }

        if (vie <= 0)
        {
            SDL_SetRenderDrawColor(renderer,0,0,0,180);
            SDL_RenderFillRect(renderer,&(SDL_Rect){0,0,1000,600});
            SDL_RenderCopy(renderer, gameover, NULL, &(SDL_Rect){300,200,400,200});
            SDL_RenderPresent(renderer);
            SDL_Delay(3000);
            running = 0;
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(heart);
    SDL_DestroyTexture(win);
    SDL_DestroyTexture(gameover);
    Mix_FreeChunk(soundTrue);
    Mix_FreeChunk(soundFalse);
    Mix_FreeChunk(winSound);
}

/**
 * @brief Charge une texture à partir d'un fichier.
 */
SDL_Texture* loadTexture(const char *file, SDL_Renderer *renderer) {
    SDL_Surface *temp = IMG_Load(file);
    if(!temp) return NULL;
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_FreeSurface(temp);
    return tex;
}

/**
 * @brief Affiche un bouton avec gestion du survol.
 */
void renderButton(Bouton *b, SDL_Renderer *renderer, int mouseX, int mouseY) {
    SDL_Texture *toRender = b->normal;
    if(mouseX >= b->rect.x && mouseX <= b->rect.x + b->rect.w && mouseY >= b->rect.y && mouseY <= b->rect.y + b->rect.h) {
        toRender = b->hover;
    }
    SDL_RenderCopy(renderer, toRender, NULL, &b->rect);
}

/**
 * @brief Vérifie si un point se trouve dans un rectangle.
 */
int checkClick(SDL_Rect rect, int mouseX, int mouseY) {
    return (mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h);
}

/**
 * @brief Charge les énigmes depuis un fichier texte.
 */
int chargerEnigmes(Enigme T[], int *n) {
    FILE *f = fopen("enigmes.txt", "r");
    if (f == NULL) return 0;
    *n = 0;
    while (fgets(T[*n].question, 256, f) != NULL) {
        T[*n].question[strcspn(T[*n].question, "\n")] = 0;
        char ligne[256];
        if(fgets(ligne, 256, f)) {
            sscanf(ligne, "%[^;];%[^;];%[^;];%d", T[*n].choix1, T[*n].choix2, T[*n].choix3, &T[*n].bonne_reponse);
            T[*n].deja_pose = 0;
            (*n)++;
        }
    }
    fclose(f);
    return 1;
}

/**
 * @brief Choisit une énigme au hasard.
 */
int choisirEnigme(Enigme T[], int n) {
    int i;
    do { i = rand() % n; } while (T[i].deja_pose == 1);
    T[i].deja_pose = 1;
    return i;
}
