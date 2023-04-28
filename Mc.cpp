#include "Mc.hpp"

//Constructeur spécial pour le MC (fait toutes les déclarations de Sprite)
Mc::Mc() : Killable("robot") {
    //std::cout << "as " << std::endl;
    //name = "robot";
    //On donne en référence le joueur pour l'utiliser plus tard
    Sprite::joueur = this;
    
    PV = 20;
    vitesse = 60.0;

    _hauteur = 64;
    _largeur = 48;

    this->setCoord(10,20,0);
    this->setOnScreen(true);
}

void Mc::get_keypress(){
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {   
        switch(event.type){

            case SDL_KEYUP :
                doKeyUp(&event.key);
                break;

            case SDL_KEYDOWN :
                doKeyDown(&event.key);

            default : break;
        }
    }
    //printf("dx : %f | dy : %f \n", dx, dy);
    this->translate(dx, dy);
}

void Mc::doKeyDown(SDL_KeyboardEvent *event)
{   
    //Pour un seul press de button
	if (event->repeat == 0)
	{  
        if(event->keysym.scancode == SDL_SCANCODE_ESCAPE){
            exit(0);
        }
        //On est actuellement en WASD
		if (event->keysym.scancode == SDL_SCANCODE_Z)
		{
            //printf("Z\n");
            dy -=vitesse;
		}
        else if (event->keysym.scancode == SDL_SCANCODE_S)
		{
            //printf("S\n"); 
            dy += vitesse;
		}

		if (event->keysym.scancode == SDL_SCANCODE_Q)
		{
            //printf("Q\n"); 
            dx -= vitesse;
		}
        else if (event->keysym.scancode == SDL_SCANCODE_D)
		{
            //printf("D\n"); 
            dx += vitesse;
		}
	}
    //Lorsque la touche est appuyé longtemps 
    else{

    }
}

void Mc::doKeyUp(SDL_KeyboardEvent *event)
{
    if (event->repeat == 0)
        {  
        //On est actuellement en WASD
        if (event->keysym.scancode == SDL_SCANCODE_Z)
        {
            //printf("Z\n");
            dy = 0;
        }
        else if (event->keysym.scancode == SDL_SCANCODE_S)
        {
            //printf("S\n"); 
            dy = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_Q)
        {
            //printf("Q\n"); 
            dx = 0;
        }
        else if (event->keysym.scancode == SDL_SCANCODE_D)
        {
            //printf("D\n"); 
            dx = 0;
        }
    }
}