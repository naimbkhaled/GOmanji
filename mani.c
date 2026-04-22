#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "animation.h"
#include "joueur.h"
#include "backg.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window *fenetre = SDL_CreateWindow("joueur",
                                           SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED,
                                           800, 600,
                                           SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(fenetre, -1, 0);

    Entite e;


    initialiserEntiteSprite(&e, renderer, "sprite.png");


    SDL_Event event;
    int continuer = 1;
    Background bg = {
        .rect = {0, 0, 400, 600},
        .imagePath = "fleur_rouge.png"
    };

    initBackground(&bg, renderer);
    
    
    Background bg2 = {
        .rect = {400, 0, 400, 600},
        .imagePath = "fleur_jaune.png"
    };
    initBackground(&bg2, renderer);
        Background bg3 = {
        .rect = {0, 0, 800, 600},
        .imagePath = "fleur_jaune.png"
    };
    initBackground(&bg3, renderer);

    
    Joueur j1;
initialiserJoueur(&j1, renderer, "sprite.png");


Joueur j11;
initialiserJoueur1(&j11, renderer, "sprite.png");


Joueur j12;
initialiserJoueur2(&j12, renderer, "sprite.png");

int largeurSprite = j1.anim.nbC * j1.anim.posSprite.w;
int state =1;



Uint32 lastTime = SDL_GetTicks();



char scoret[50];
sprintf(scoret, "%d", j1.score);  



char scoret1[50];
sprintf(scoret1, "%d", j11.score);



char scoret2[50];
sprintf(scoret2, "%d", j12.score);

SDL_Surface *surface = IMG_Load("life.png");
j1.vieImg = SDL_CreateTextureFromSurface(renderer, surface);
j11.vieImg = SDL_CreateTextureFromSurface(renderer, surface);
j12.vieImg = SDL_CreateTextureFromSurface(renderer, surface);
SDL_FreeSurface(surface);



    
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("Pixeboy.ttf", 25);
    SDL_Color couleur = {0, 0, 0};
    SDL_Texture *textTexture = NULL;
    SDL_Surface *textSurface ;
    SDL_Rect textPosition = {700, 50, 0, 0}; 
    SDL_Rect textPosition1 = {300, 50, 0, 0}; 
    SDL_Rect textPosition2 = {700, 50, 0, 0}; 
    textSurface=TTF_RenderText_Solid(font, scoret,couleur);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    

    SDL_Texture *textTexture1 = NULL;
    SDL_Surface *textSurface1 ;    
    textSurface1=TTF_RenderText_Solid(font, scoret1,couleur);
    textTexture1 = SDL_CreateTextureFromSurface(renderer, textSurface1);
    
    
    
    SDL_Texture *textTexture2 = NULL;
    SDL_Surface *textSurface2 ;    
    textSurface2=TTF_RenderText_Solid(font, scoret2,couleur);
    textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
    




while (continuer)
{
SDL_RenderClear(renderer);

    Uint32 currentTime = SDL_GetTicks();
int dt = currentTime - lastTime;
lastTime = currentTime;

    while (SDL_PollEvent(&event))
    {
    	if (event.type == SDL_QUIT)
                continuer = 0;
        if (state==1){
	if (event.key.keysym.sym == SDLK_2){state=2;}}
        else if (state==2){
	if (event.key.keysym.sym == SDLK_1){state=1;}}
        deplacerJoueur(&j1, event);
        deplacerJoueur1(&j11, event);
        deplacerJoueur2(&j12, event);
        
        
        

    }
    SDL_QueryTexture(textTexture, NULL, NULL, &textPosition.w, &textPosition.h);
    sprintf(scoret, "%d", j1.score);
    textSurface=TTF_RenderText_Solid(font, scoret,couleur);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    
    
    SDL_QueryTexture(textTexture2, NULL, NULL, &textPosition2.w, &textPosition2.h);
    sprintf(scoret2, "%d", j12.score);
    textSurface2=TTF_RenderText_Solid(font, scoret2,couleur);
    textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
    
    
    SDL_QueryTexture(textTexture1, NULL, NULL, &textPosition1.w, &textPosition1.h);
    sprintf(scoret1, "%d", j11.score);
    textSurface1=TTF_RenderText_Solid(font, scoret1,couleur);
    textTexture1 = SDL_CreateTextureFromSurface(renderer, textSurface1);
    

    
        saut(&j1, dt);
        saut1(&j11, dt);
        saut2(&j12, dt);


    SDL_RenderClear(renderer);
    if (state==1){
    renderBackground(renderer, &bg3);
    afficherJoueur(j1, renderer);
    afficherVies(j1, renderer);
    afficherEnergie(j1,renderer);
    SDL_RenderCopy(renderer, textTexture, NULL, &textPosition );
    }
    else{
    renderBackground(renderer, &bg);
    renderBackground(renderer, &bg2);
    afficherJoueur(j11, renderer);
    afficherVies1(j11, renderer);
    afficherJoueur(j12, renderer);
    afficherVies2(j12, renderer);
        SDL_RenderCopy(renderer, textTexture1, NULL, &textPosition1 );
            SDL_RenderCopy(renderer, textTexture2, NULL, &textPosition2 );
    }


    SDL_RenderPresent(renderer);
}

    freeBackground(&bg);
    freeBackground(&bg2);
    freeBackground(&bg3);
    libererEntite(&e);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    
    
    
    TTF_CloseFont(font);
    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(textTexture1);
    SDL_DestroyTexture(textTexture2);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
