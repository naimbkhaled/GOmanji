/**
 * @file main.c
 * @brief Programme principal du jeu.
 */

#include "header.h"

/**
 * @brief Fonction principale.
 */
int main(void)
{
    Game game;

    int running = 1;

    if(!initGame(&game))
        return -1;

    while(running)
    {
        handleInput(&game,&running);

        updateGame(&game);

        renderGame(&game);

        SDL_Delay(16);
    }

    cleanGame(&game);

    return 0;
}
