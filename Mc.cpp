#include "Mc.hpp"

//Constructeur spécial pour le MC (renseigne Sprite::joueur)
Mc::Mc() {
    //On donne en référence le joueur pour l'utiliser plus tard
    Sprite::joueur = this;
    
    PV = 20;
    PVMax = PV;

    depForce = BASICSPEED;
    dashValue = 4.0;

    _hauteur = 64;
    _largeur = 48;
    rayon = 24;
    masse = 20;
    frottements = 350;

    _coord[0] = 200;
    _coord[1] = 200;

    this->setCoord(10,20,0);
    onScreen = true;
    
    states = &(etatsDesMc);
    maxDelay = 20; // Change de frame tous les 20 ticks

    cdDashTime = SDL_GetTicks();

    speed.redef(0,0);

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
            depForce = BASICSPEED;
            cdDashTime = SDL_GetTicks();
        }
    }

    //faire test de direction ici;
    attack->update(dx, dy);

    //Calcul de la force que le MC veut rajouter
    Vector2D v(pushForceD - pushForceG, pushForceB - pushForceH);
    move(v);

    // On change la vitesse actuelle du Mc en fonction des forces appliquées sur lui et des collisions
    accelerateWithForce(v.x, v.y);
    
    // Les collisions dépendent des itérations de déplacement
    Killable::updateSpeedWithCollisions();

    translate(speed);
}

void Mc::get_keypress(){
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {   
        switch(event.type){

            case SDL_KEYUP :
                doKeyUp(event.key);
                break;

            case SDL_KEYDOWN :
                doKeyDown(event.key);

            case SDL_MOUSEBUTTONDOWN:
                //do whatever you want to do after a mouse button was pressed,
                mousePress(event.button);
                break;

            default : break;
        }
    }
    
    //printf("dx : %f | dy : %f \n", dx, dy);
}

void Mc::doKeyDown(SDL_KeyboardEvent &event)
{   
    // Pour un seul press de button
	if (event.repeat == 0)
	{ 
        switch(event.keysym.sym) {
            case SDLK_ESCAPE :
                exit(0);
            
            case SDLK_SPACE :
                if( (SDL_GetTicks() - cdDashTime) > 200){
                    depForce *= dashValue;
                    startDashTime = SDL_GetTicks();
                    dashOn = true;
                }else{
                    std::cout << "Cooldown en cours" << std::endl;
                }
                break;

            case SDLK_z :
                pushForceH = 1;
                break;
            case SDLK_s :
                pushForceB = 1;
                break;
            case SDLK_q :
                pushForceG = 1;
                break;
            case SDLK_d :
                pushForceD = 1;
                break;
        }
    }
}

void Mc::doKeyUp(SDL_KeyboardEvent &event) {
    switch(event.keysym.sym) {
        case SDLK_ESCAPE :
            exit(0);
        
        case SDLK_SPACE :
            if( (SDL_GetTicks() - cdDashTime) > 200){
                depForce *= dashValue;
                startDashTime = SDL_GetTicks();
                dashOn = true;
            }else{
                std::cout << "Cooldown en cours" << std::endl;
            }
            
            break;

        case SDLK_z :
            pushForceH = 0;
            break;
        case SDLK_s :
            pushForceB = 0;
            break;
        case SDLK_q :
            pushForceG = 0;
            break;
        case SDLK_d :
            pushForceD = 0;
            break;
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