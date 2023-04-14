#include "Mc.hpp"


Mc::Mc(std::string& defaultName, Affichage& aff) : Entite(defaultName, aff) {
    name = defaultName;
    PV = 20;
    vitesse = 1.5;

    _hauteur = 64;
    _largeur = 48;

    this->setCoord(10,20,0);
    this->setOnScreen(true);
}

void Mc::get_keypress(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type){
        
        case SDL_KEYUP :
            break;

        case SDL_KEYDOWN :
            doKeyDown(&event.key);

        default : break;
    }
}

void Mc::doKeyDown(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_Z)
		{
            printf("Z\n");
            this->translate(0, -vitesse);
		}
        else if (event->keysym.scancode == SDL_SCANCODE_S)
		{
            printf("S\n"); 
            this->translate(0, vitesse);
		}

		if (event->keysym.scancode == SDL_SCANCODE_Q)
		{
            printf("Q\n"); 
            this->translate(-vitesse, 0);
		}
        else if (event->keysym.scancode == SDL_SCANCODE_D)
		{
            printf("D\n"); 
            this->translate(vitesse, 0);
		}

        if(event->keysym.scancode == SDL_SCANCODE_ESCAPE){
            exit(0);
        }
	}
}