#include "Mc.hpp"

//Constructeur spécial pour le MC (renseigne Sprite::joueur)
Mc::Mc() {
    //std::cout << "as " << std::endl;
    //name = "robot";
    //On donne en référence le joueur pour l'utiliser plus tard
    Sprite::joueur = this;
    
    PV = 20;
    PVMax = PV;

    vitesse = 150.0;
    dashValue = 4.0;

    _hauteur = 64;
    _largeur = 48;
    rayon = 24;

    this->setCoord(10,20,0);
    onScreen = true;
    
    states = &(etatsDesMc);
    maxDelay = 20; // Change de frame tous les 20 ticks

    cdDashTime = SDL_GetTicks();

    std::cout << "Création de Mc : " << states->spriteName << std::endl;

    autoSetHitBox();
    addSprite();
    attack = new Attacks(this);
}

void Mc::update() {
    Sprite::update();
    if(!dashOn){
        get_keypress();
    }else{
        //Regarde si le temps de dash est fini (bloque les autres mouvement)
        actualDashTime = SDL_GetTicks() - startDashTime;
        //std::cout << actualDashTime << std::endl;
        if(actualDashTime > 1000/dashValue){
            dashOn = false;
            vitesse /= dashValue;
            cdDashTime = SDL_GetTicks();
        }
    }

    //faire test de direction ici;
    attack->update(dx, dy);
    Vector2D v(dx, dy);
    moveAllCollision(Sprite::map->getEntities(), move(v));
    translate(v);
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
    
}

void Mc::doKeyDown(SDL_KeyboardEvent *event)
{   
    //Pour un seul press de button
	if (event->repeat == 0)
	{  
        if(event->keysym.scancode == SDL_SCANCODE_ESCAPE){
            exit(0);
        }

        if (event->keysym.scancode == SDL_SCANCODE_SPACE){
            //std::cout << "dash" << std::endl;
            //std::cout << "direction dx " << dx << " dy : "<< dy  << std::endl;
            if( (SDL_GetTicks() - cdDashTime) > 200){
                vitesse *= dashValue;
                startDashTime = SDL_GetTicks();
                dashOn = true;
            }else{
                std::cout << "Cooldown en cours" << std::endl;
            }
        }
        
        //On est actuellement en ZQSD
		if (event->keysym.scancode == SDL_SCANCODE_W)
		{
            //printf("Z\n");
            dy = -1;
		}
        else if (event->keysym.scancode == SDL_SCANCODE_S)
		{
            //printf("S\n"); 
            dy = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_A)
		{
            //printf("Q\n"); 
            dx = -1;
		}
        else if (event->keysym.scancode == SDL_SCANCODE_D)
		{
            //printf("D\n"); 
            dx = 1;
		}

        if (event->keysym.scancode == SDL_SCANCODE_J)
		{
            //light
            attack->updateAttack(1);
		}
        else if(event->keysym.scancode == SDL_SCANCODE_K){
            //heavy
            attack->updateAttack(2);
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
            if(dy < 0){
                //printf("Z\n");
                dy = 0;
            }
        }
        else if (event->keysym.scancode == SDL_SCANCODE_S)
        {
            if(dy > 0){
                //printf("S\n"); 
                dy = 0;
            }
        }

        if (event->keysym.scancode == SDL_SCANCODE_A)
        {
            if(dx < 0){
                //printf("Q\n"); 
                dx = 0;
            }
        }
        else if (event->keysym.scancode == SDL_SCANCODE_D)
        {
            if(dx > 0){
                //printf("D\n"); 
                dx = 0;
            }
        }

        if (event->keysym.scancode == SDL_SCANCODE_SPACE){
            //std::cout << "release dash" << std::endl;
        }
    }
}