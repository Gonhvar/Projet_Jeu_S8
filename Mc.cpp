#include "Mc.hpp"

//Constructeur spécial pour le MC (renseigne Sprite::joueur)
Mc::Mc() {
    //On donne en référence le joueur pour l'utiliser plus tard
    Sprite::joueur = this;
    
    PV = 20;
    PVMax = PV;

    vitesse = BASICSPEED;
    dashValue = 4.0;

    _hauteur = 64;
    _largeur = 48;
    rayon = 24;
    masse = 40;

    _coord[0] = 200;
    _coord[1] = 200;

    this->setCoord(10,20,0);
    onScreen = true;
    
    states = &(etatsDesMc);
    maxDelay = 20; // Change de frame tous les 20 ticks

    cdDashTime = SDL_GetTicks();


    autoSetHitBox();
    addSprite();
    attack = new Attacks(this);
    //std::cout << "Création de Mc : " << states->spriteName << std::endl;
}

void Mc::update() {

    if(!dashOn){
        get_keypress();
    }else{
        //Regarde si le temps de dash est fini (bloque les autres mouvement)
        actualDashTime = SDL_GetTicks() - startDashTime;
        //std::cout << actualDashTime << std::endl;
        if(actualDashTime > 1000/dashValue){
            dashOn = false;
            vitesse = BASICSPEED;
            cdDashTime = SDL_GetTicks();
        }
    }

    //faire test de direction ici;
    attack->update(dx, dy);

    Vector2D v(dx, dy);
    move(v);
    moveAllCollision(v);
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

            case SDL_MOUSEBUTTONDOWN:
                //do whatever you want to do after a mouse button was pressed,
                mousePress(event.button);
                break;

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

void Mc::mousePress(SDL_MouseButtonEvent& b){
    if(b.button == SDL_BUTTON_LEFT){
        //handle a left-click
        std::cout << "Bang !" << std::endl;
        SDL_GetMouseState(&mouseX, &mouseY);
        stockeur->getJ2()->newTir(0, mouseX, mouseY);
    }
}

Attacks* Mc::getAttack(){
    return attack;
}