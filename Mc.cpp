#include "Mc.hpp"

//Constructeur spécial pour le MC (renseigne Sprite::joueur)
Mc::Mc() {
    //std::cout << "as " << std::endl;
    //name = "robot";
    //On donne en référence le joueur pour l'utiliser plus tard
    Sprite::joueur = this;
    
    PV = 20;
    PVMax = PV;

    vitesse = 75.0;

    _hauteur = 64;
    _largeur = 48;

    this->setCoord(10,20,0);
    this->setOnScreen(true);
    
    states = &(etatsDesMc);
    maxDelay = 20; // Change de frame tous les 20 ticks

    std::cout << "Création de Mc : " << states->spriteName << std::endl;

    addSprite();
}

void Mc::update() {
    Sprite::update();
    get_keypress();
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
    move(dx, dy);
}

void Mc::doKeyDown(SDL_KeyboardEvent *event)
{   
    //Pour un seul press de button
	if (event->repeat == 0)
	{  
        if(event->keysym.scancode == SDL_SCANCODE_ESCAPE){
            exit(0);
        }
        //On est actuellement en ZQSD
		if (event->keysym.scancode == SDL_SCANCODE_W)
		{
            //printf("Z\n");
            dy = -vitesse;
		}
        else if (event->keysym.scancode == SDL_SCANCODE_S)
		{
            //printf("S\n"); 
            dy = vitesse;
		}

		if (event->keysym.scancode == SDL_SCANCODE_A)
		{
            //printf("Q\n"); 
            dx = -vitesse;
		}
        else if (event->keysym.scancode == SDL_SCANCODE_D)
		{
            //printf("D\n"); 
            dx = vitesse;
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
        //On est actuellement en ZQSD
        if (event->keysym.scancode == SDL_SCANCODE_W)
        {
            //printf("Z\n");
            dy = 0;
        }
        else if (event->keysym.scancode == SDL_SCANCODE_S)
        {
            //printf("S\n"); 
            dy = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_A)
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