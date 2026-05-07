/**
 * @file source.c
 * @brief Gestion du jeu SDL2.
 */

#include "header.h"

/**
 * @brief Initialise les plateformes.
 * @param lp Liste des plateformes.
 * @param r Renderer SDL.
 * @param level Niveau actuel.
 */
void initPlateformes(ListePlateformes *lp, SDL_Renderer *r, int level)
{
    lp->nb = 0;

    SDL_Texture *f = IMG_LoadTexture(r, "plat1.png");
    SDL_Texture *m = IMG_LoadTexture(r, "plat2.png");
    SDL_Texture *d = IMG_LoadTexture(r, "plat3.png");

    if(level == 1)
    {
        lp->nb = 2;

        lp->p[0] = (Plateforme){{500,400,150,50},f,FIXE,0,0,1};
        lp->p[1] = (Plateforme){{900,350,150,50},f,FIXE,0,0,1};
    }

    if(level == 2)
    {
        lp->nb = 3;

        lp->p[0] = (Plateforme){{400,400,150,50},f,FIXE,0,0,1};
        lp->p[1] = (Plateforme){{800,300,150,50},m,MOBILE,1,3,1};
        lp->p[2] = (Plateforme){{1200,350,150,50},f,FIXE,0,0,1};
    }

    if(level == 3)
    {
        lp->nb = 4;

        lp->p[0] = (Plateforme){{400,400,150,50},f,FIXE,0,0,1};
        lp->p[1] = (Plateforme){{700,300,150,50},m,MOBILE,1,4,1};
        lp->p[2] = (Plateforme){{1000,350,150,50},d,DESTRUCTIBLE,0,0,1};
        lp->p[3] = (Plateforme){{1300,250,150,50},f,FIXE,0,0,1};
    }
}

/**
 * @brief Met à jour les plateformes mobiles.
 * @param lp Liste des plateformes.
 */
void updatePlateformes(ListePlateformes *lp)
{
    for(int i=0;i<lp->nb;i++)
    {
        if(lp->p[i].type == MOBILE)
        {
            lp->p[i].rect.x += lp->p[i].dir * lp->p[i].speed;

            if(lp->p[i].rect.x > 900 || lp->p[i].rect.x < 400)
                lp->p[i].dir *= -1;
        }
    }
}

/**
 * @brief Affiche les plateformes.
 * @param lp Liste des plateformes.
 * @param r Renderer SDL.
 * @param camX Position caméra.
 */
void renderPlateformes(ListePlateformes *lp, SDL_Renderer *r, int camX)
{
    for(int i=0;i<lp->nb;i++)
    {
        if(!lp->p[i].alive)
            continue;

        SDL_Rect rr = lp->p[i].rect;

        rr.x -= camX;

        SDL_RenderCopy(r, lp->p[i].texture, NULL, &rr);
    }
}

/**
 * @brief Détruit les textures des plateformes.
 * @param lp Liste des plateformes.
 */
void destroyPlateformes(ListePlateformes *lp)
{
    for(int i=0;i<lp->nb;i++)
        SDL_DestroyTexture(lp->p[i].texture);
}

/**
 * @brief Initialise le timer.
 * @param t Timer.
 */
void initTimer(Timer *t)
{
    t->startTicks = SDL_GetTicks();
}

/**
 * @brief Affiche le timer.
 * @param t Timer.
 * @param renderer Renderer SDL.
 * @param font Police utilisée.
 */
void renderTimer(Timer *t, SDL_Renderer *renderer, TTF_Font *font)
{
    Uint32 elapsed = SDL_GetTicks() - t->startTicks;

    int sec = (elapsed / 1000) % 60;
    int min = (elapsed / 60000);

    char txt[32];

    sprintf(txt, "Time: %02d:%02d", min, sec);

    SDL_Color c = {255,255,255,255};

    SDL_Surface *s =
    TTF_RenderText_Blended(font, txt, c);

    SDL_Texture *tex =
    SDL_CreateTextureFromSurface(renderer, s);

    SDL_Rect r = {10,550,s->w,s->h};

    SDL_FreeSurface(s);

    SDL_RenderCopy(renderer, tex, NULL, &r);

    SDL_DestroyTexture(tex);
}

/**
 * @brief Initialise un guide.
 * @param g Guide.
 * @param renderer Renderer SDL.
 * @param path Chemin image.
 */
void initGuide(Guide *g, SDL_Renderer *renderer, const char *path)
{
    g->texture = IMG_LoadTexture(renderer, path);

    if(!g->texture)
        printf("Erreur chargement %s: %s\n", path, IMG_GetError());

    g->active = 0;
    g->startTime = 0;
}

/**
 * @brief Active un guide.
 * @param g Guide.
 * @param timed Affichage temporaire.
 */
void showGuide(Guide *g, int timed)
{
    g->active = 1;

    if(timed)
        g->startTime = SDL_GetTicks();
    else
        g->startTime = 0;
}

/**
 * @brief Met à jour le guide.
 * @param g Guide.
 */
void updateGuide(Guide *g)
{
    if(g->active && g->startTime != 0 &&
       SDL_GetTicks() - g->startTime > 3000)
    {
        g->active = 0;
    }
}

/**
 * @brief Affiche le guide.
 * @param g Guide.
 * @param renderer Renderer SDL.
 */
void renderGuide(Guide *g, SDL_Renderer *renderer)
{
    if(!g->active || !g->texture)
        return;

    SDL_Rect r = {250,150,500,300};

    SDL_RenderCopy(renderer, g->texture, NULL, &r);
}

/**
 * @brief Initialise le jeu.
 * @param g Structure Game.
 * @return 1 si succès.
 */
int initGame(Game *g)
{
    SDL_Init(SDL_INIT_VIDEO);

    IMG_Init(IMG_INIT_PNG);

    TTF_Init();

    g->window = SDL_CreateWindow(
        "Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0);

    g->renderer =
    SDL_CreateRenderer(
        g->window,
        -1,
        SDL_RENDERER_ACCELERATED);

    g->font = TTF_OpenFont("arial.ttf",30);

    g->camera =
    (SDL_Rect){0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

    g->cameraRight = g->camera;

    g->segments[0].background =
    IMG_LoadTexture(g->renderer,"background.png");

    g->segments[1].background =
    IMG_LoadTexture(g->renderer,"background2.png");

    g->segments[2].background =
    IMG_LoadTexture(g->renderer,"background3.png");

    g->currentBG = 0;
    g->level = 1;

    initPlateformes(&g->plateformes,g->renderer,g->level);

    initTimer(&g->timer);

    initGuide(&g->guide,g->renderer,"guide.png");

    initGuide(&g->levelGuide,g->renderer,"niv.png");

    g->multi = 0;

    return 1;
}

/**
 * @brief Gère les événements clavier.
 * @param g Structure Game.
 * @param running Etat du jeu.
 */
void handleInput(Game *g, int *running)
{
    SDL_Event e;

    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
            *running = 0;

        if(e.type == SDL_KEYDOWN)
        {
            int texW, texH;

            SDL_QueryTexture(
                g->segments[g->currentBG].background,
                NULL,NULL,
                &texW,&texH);

            int maxX = texW - SCREEN_WIDTH;

            switch(e.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    *running = 0;
                    break;

                case SDLK_g:
                    g->guide.active = !g->guide.active;
                    break;

                case SDLK_m:
                    g->multi = !g->multi;
                    break;

                case SDLK_RIGHT:
                    g->camera.x += 20;

                    if(g->camera.x > maxX)
                        g->camera.x = maxX;
                    break;

                case SDLK_LEFT:
                    g->camera.x -= 20;
                    break;

                case SDLK_d:
                    g->cameraRight.x += 20;

                    if(g->cameraRight.x > maxX)
                        g->cameraRight.x = maxX;
                    break;

                case SDLK_q:
                    g->cameraRight.x -= 20;

                    if(g->cameraRight.x < 0)
                        g->cameraRight.x = 0;
                    break;
            }
        }
    }
}

/**
 * @brief Met à jour le jeu.
 * @param g Structure Game.
 */
void updateGame(Game *g)
{
    int texW, texH;

    SDL_QueryTexture(
        g->segments[g->currentBG].background,
        NULL,NULL,
        &texW,&texH);

    int maxX = texW - SCREEN_WIDTH;

    if(g->camera.x >= maxX)
    {
        if(g->currentBG < 2)
        {
            g->currentBG++;
            g->level++;

            g->camera.x = 0;
            g->cameraRight.x = 0;

            initPlateformes(
                &g->plateformes,
                g->renderer,
                g->level);

            showGuide(&g->levelGuide,1);
        }

        else
        {
            g->camera.x = maxX;
        }
    }

    updatePlateformes(&g->plateformes);

    updateGuide(&g->levelGuide);
}

/**
 * @brief Dessine une vue du jeu.
 */
static void draw(Game *g,int camX,int camY,SDL_Rect view)
{
    SDL_RenderSetViewport(g->renderer,&view);

    int texW, texH;

    SDL_QueryTexture(
        g->segments[g->currentBG].background,
        NULL,NULL,
        &texW,&texH);

    if(camX < 0)
        camX = 0;

    if(camX > texW - view.w)
        camX = texW - view.w;

    SDL_Rect src = {camX,camY,view.w,view.h};

    SDL_Rect dst = {0,0,view.w,view.h};

    SDL_RenderCopy(
        g->renderer,
        g->segments[g->currentBG].background,
        &src,
        &dst);

    renderPlateformes(
        &g->plateformes,
        g->renderer,
        camX);
}

/**
 * @brief Affiche le jeu.
 * @param g Structure Game.
 */
void renderGame(Game *g)
{
    SDL_RenderClear(g->renderer);

    if(!g->multi)
    {
        SDL_Rect full =
        {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

        draw(
            g,
            g->camera.x,
            g->camera.y,
            full);
    }

    else
    {
        SDL_Rect left =
        {0,0,SCREEN_WIDTH/2,SCREEN_HEIGHT};

        SDL_Rect right =
        {SCREEN_WIDTH/2,0,
         SCREEN_WIDTH/2,SCREEN_HEIGHT};

        draw(
            g,
            g->camera.x,
            g->camera.y,
            left);

        draw(
            g,
            g->cameraRight.x,
            g->cameraRight.y,
            right);
    }

    renderTimer(
        &g->timer,
        g->renderer,
        g->font);

    renderGuide(
        &g->guide,
        g->renderer);

    renderGuide(
        &g->levelGuide,
        g->renderer);

    SDL_RenderPresent(g->renderer);
}

/**
 * @brief Libère les ressources du jeu.
 * @param g Structure Game.
 */
void cleanGame(Game *g)
{
    destroyPlateformes(&g->plateformes);

    for(int i=0;i<3;i++)
        SDL_DestroyTexture(g->segments[i].background);

    SDL_DestroyTexture(g->guide.texture);

    SDL_DestroyTexture(g->levelGuide.texture);

    TTF_CloseFont(g->font);

    SDL_DestroyRenderer(g->renderer);

    SDL_DestroyWindow(g->window);

    IMG_Quit();

    TTF_Quit();

    SDL_Quit();
}
