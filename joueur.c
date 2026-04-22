#include "joueur.h"
void initialiserJoueur(Joueur *j, SDL_Renderer *renderer, char image[])
{

    initialiserEntiteSprite(&j->anim, renderer, image);

    j->score = 0;
    j->vies = 3;
    
    

    
    
    
    j->up = 0;
    j->x_rel = -50;   // point A
    j->c = 100;       // hauteur saut
    j->a = -0.04;     // calcul du PDF
    j->posinit = j->anim.posEcran.y;
    
    
    
    j->dirX = 1; 
    
    j->energie = 100;
    j->energieMax = 100;
}

void initialiserJoueur1(Joueur *j, SDL_Renderer *renderer, char image[])
{

    initialiserEntiteSprite1(&j->anim, renderer, image);

    j->score = 0;
    j->vies = 3;
    
    

    
    
    j->up = 0;
j->x_rel = -50;   // point A
j->c = 100;       // hauteur saut
j->a = -0.04;     
j->posinit = j->anim.posEcran.y;



j->dirX = 1; 
}



void initialiserJoueur2(Joueur *j, SDL_Renderer *renderer, char image[])
{
    initialiserEntiteSprite2(&j->anim, renderer, image);

    j->score = 0;
    j->vies = 3;
    
    
    

    
    
    j->up = 0;
j->x_rel = -50;   // point A
j->c = 100;       // hauteur saut
j->a = -0.04;     // calcul du PDF
j->posinit = j->anim.posEcran.y;



j->dirX = 1;
}


void afficherJoueur(Joueur j, SDL_Renderer *renderer)
{
    afficherEntite(j.anim, renderer);
}



void animerJoueur(Joueur *j, int largeurSprite)
{
    animerEntiteSprite(&j->anim, largeurSprite);
}

void deplacerJoueur(Joueur *j, SDL_Event event)
{


    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    int vitesse = 5;


    if (keystate[SDL_SCANCODE_G] && j->energie > 0)
    {
    if (j->energie <= 10)
    vitesse = 5;
        else vitesse = 10;
        j->energie -= 0.5;
    }
    else
    {
        if (j->energie < j->energieMax)
            j->energie += 0.2;
    }
    if (j->energie < 0)
    j->energie = 0;

if (j->energie > j->energieMax)
    j->energie = j->energieMax;
    




    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_RIGHT)
        {
            j->anim.direction = 0;
            j->dirX = 1;
            if (j->anim.posEcran.x!=700) j->anim.posEcran.x += vitesse;
            animerJoueur(j, j->anim.posSprite.w * j->anim.nbC);
            j->score = j->score + 2;
        }
        else if (event.key.keysym.sym == SDLK_LEFT)
        {
            j->anim.direction = 1;
            j->dirX = -1;
            if (j->anim.posEcran.x!=-30) j->anim.posEcran.x -= vitesse;
            animerJoueur(j, j->anim.posSprite.w * j->anim.nbC);
	    j->score = j->score + 2;
        }
        if (event.key.keysym.sym == SDLK_UP && j->up == 0)
        {
    		j->up = 1;
    		j->x_rel = -50; 
	        j->score = j->score + 1;    		
	}
	if (event.key.keysym.sym == SDLK_SPACE) 
        {
            attaquer(j);
        }

    }
}

void deplacerJoueur1(Joueur *j, SDL_Event event)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_RIGHT)
        {
            j->anim.direction = 0;
            j->dirX = 1;
            if (j->anim.posEcran.x!=300)j->anim.posEcran.x += 10;
            animerJoueur(j, j->anim.posSprite.w * j->anim.nbC);
            j->score = j->score + 2;
        }
        else if (event.key.keysym.sym == SDLK_LEFT)
        {
            j->anim.direction = 1;
            j->dirX = -1;
            if (j->anim.posEcran.x!=-30)j->anim.posEcran.x -= 10;
            animerJoueur(j, j->anim.posSprite.w * j->anim.nbC);
            j->score = j->score + 2;
        }
        if (event.key.keysym.sym == SDLK_UP && j->up == 0)
        {
            j->up = 1;
            j->x_rel = -50; // reset départ
            j->score = j->score + 1;
        }
        if (event.key.keysym.sym == SDLK_a) 
        {
            attaquer(j);
        }
    }
}
void deplacerJoueur2(Joueur *j, SDL_Event event)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_d)
        {
            j->anim.direction = 0;
            j->dirX = 1;
            if (j->anim.posEcran.x!=700)j->anim.posEcran.x += 10;
            animerJoueur(j, j->anim.posSprite.w * j->anim.nbC);
            j->score = j->score + 2;
        }
        else if (event.key.keysym.sym == SDLK_q)
        {
            j->anim.direction = 1;
            j->dirX = -1;
            if (j->anim.posEcran.x!=370)j->anim.posEcran.x -= 10;
            animerJoueur(j, j->anim.posSprite.w * j->anim.nbC);
            j->score = j->score + 2;
        }
        if (event.key.keysym.sym == SDLK_z && j->up == 0)
        {
            j->up = 1;
            j->x_rel = -50; // reset départ
            j->score = j->score + 1;
        }
        if (event.key.keysym.sym == SDLK_n)
        {
            attaquer(j);
        }
    }
}





void saut(Joueur *j, int dt)
{
    if (j->up == 1)
    {
    
        j->anim.direction = 1; 
    animerJoueur(j, j->anim.posSprite.w * j->anim.nbC);

        j->x_rel += 0.2 * dt;

        // appliquer déplacement horizontal réel
        j->anim.posEcran.x += 2 * j->dirX;
        
        
        
        
        if (j->anim.posEcran.x < -30)
            j->anim.posEcran.x = -30;

        if (j->anim.posEcran.x > 700)
            j->anim.posEcran.x = 700;
            
            
            

        // calcul parabole
        float y = j->a * j->x_rel * j->x_rel + j->c;

        // appliquer Y
        j->anim.posEcran.y = j->posinit - y;

        // fin saut
        if (j->x_rel >= 50)
        {
            j->up = 0;
            j->x_rel = -50;
            j->anim.posEcran.y = j->posinit;
        }
    }
}

void saut1(Joueur *j, int dt)
{

    
    
    
    if (j->up == 1)
    {
        j->anim.direction = 1; 
    animerJoueur(j, j->anim.posSprite.w * j->anim.nbC);
        j->x_rel += 0.2 * dt;

        // appliquer déplacement horizontal réel
        j->anim.posEcran.x += 2 * j->dirX;
        
        
        
        
        if (j->anim.posEcran.x < -30)
            j->anim.posEcran.x = -30;

        if (j->anim.posEcran.x > 300)
            j->anim.posEcran.x = 300;
            
            
            

        // calcul parabole
        float y = j->a * j->x_rel * j->x_rel + j->c;

        // appliquer Y
        j->anim.posEcran.y = j->posinit - y;

        // fin saut
        if (j->x_rel >= 50)
        {
            j->up = 0;
            j->x_rel = -50;
            j->anim.posEcran.y = j->posinit;
        }
    }
}


void saut2(Joueur *j, int dt)
{
    if (j->up == 1)
    {
    
        j->anim.direction = 1; 
    animerJoueur(j, j->anim.posSprite.w * j->anim.nbC);

        j->x_rel += 0.2 * dt;

        // appliquer déplacement horizontal réel
        j->anim.posEcran.x += 2 * j->dirX;
        
        
        
        
        if (j->anim.posEcran.x < 370)
            j->anim.posEcran.x = 370;

        if (j->anim.posEcran.x > 700)
            j->anim.posEcran.x = 700;
            
            
            

        // calcul parabole
        float y = j->a * j->x_rel * j->x_rel + j->c;

        // appliquer Y
        j->anim.posEcran.y = j->posinit - y;

        // fin saut
        if (j->x_rel >= 50)
        {
            j->up = 0;
            j->x_rel = -50;
            j->anim.posEcran.y = j->posinit;
        }
    }
}

void afficherVies(Joueur j, SDL_Renderer *renderer)
{
    SDL_Rect posVie;

    posVie.y = 40;     
    posVie.w = 30;     
    posVie.h = 30;     

    for (int i = 0; i < j.vies; i++)
    {
        posVie.x = 20 + i * 30; 
        SDL_RenderCopy(renderer, j.vieImg, NULL, &posVie);
    }
}


void afficherVies1(Joueur j, SDL_Renderer *renderer)
{
    SDL_Rect posVie;

    posVie.y = 40;  
    posVie.w = 20;     
    posVie.h = 20;     

    for (int i = 0; i < j.vies; i++)
    {
        posVie.x = 20 + i * 20; 
        SDL_RenderCopy(renderer, j.vieImg, NULL, &posVie);
    }
}


void afficherVies2(Joueur j, SDL_Renderer *renderer)
{
    SDL_Rect posVie;

    posVie.y = 40;   
    posVie.w = 20;   
    posVie.h = 20;    

    for (int i = 0; i < j.vies; i++)
    {
        posVie.x = 420 + i * 20; 
        SDL_RenderCopy(renderer, j.vieImg, NULL, &posVie);
    }
}



void attaquer(Joueur *j)
{
    j->anim.direction = 1; 
    animerJoueur(j, j->anim.posSprite.w * j->anim.nbC);


    j->anim.posEcran.x += 2 * j->dirX;


    if (j->anim.posSprite.x >= (j->anim.nbC - 1) * j->anim.posSprite.w)
    {
        j->anim.posSprite.x = 0;
    if (j->dirX == 1)
        j->anim.direction = 0;
    else
        j->anim.direction = 1;
    }
}

void afficherEnergie(Joueur j, SDL_Renderer *renderer)
{
    SDL_Rect fond, barre;

    fond.x = 20;
    fond.y = 80;
    fond.w = 100;
    fond.h = 10;

    barre.x = 20;
    barre.y = 80;
    barre.w = (j.energie / j.energieMax) * 100;
    barre.h = 10;
        

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    
    SDL_RenderFillRect(renderer, &fond);
if (j.energie < 30)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    else
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &barre);

}







