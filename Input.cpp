#include "Input.hpp"

/* CONSTRUCTEURS ET DESTRUCTEURS */
Input::Input(){
	//std::cout <<"CREATION INPUT" << std::endl;

	dashValue = stockeur->getMc()->getDashValue();

	_hauteur = 32;
    _largeur = 32;

	States* newStates = new States(); // newStates est un pointeur temporaire
		newStates->spriteName = "noTexture"; //Mettre un viseur 
		newStates->nbEtats = 1;
		newStates->nbFrameParEtat[0] = 1;
		for (int i=1; i<newStates->nbEtats; i++) {
			newStates->nbFrameParEtat[i] = 0;
		}

        stateRect.w = 32;
        stateRect.h = 32;

		states = newStates;
		
	onScreen = true;
	addSprite();
}

void Input::update(){
	
	SDL_GetMouseState(&mouseX, &mouseY);
	_coord[0] = mouseX;
	_coord[1] = mouseY;

    if(stockeur->getMc() != nullptr){
        get_keypress();
    }
    else{
        get_otherkeypress();
    }
}

void Input::get_keypress(){
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

void Input::get_otherkeypress(){
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {   
        switch(event.type){
            case SDL_KEYDOWN :
                doOtherKeyDown(event.key);
            default : break;
        }
    }
}

void Input::doKeyDown(SDL_KeyboardEvent &event)
{   
    // Pour un seul press de button
	if (event.repeat == 0)
	{ 
        switch(event.keysym.sym) {
            case SDLK_ESCAPE :
                exit(0);
            
            case SDLK_SPACE :
                if( !(stockeur->getMc()->getDashOn())){
                    stockeur->getMc()->getDepForce() *= dashValue;
                    stockeur->getMc()->setStartDashTime(SDL_GetTicks());
                    stockeur->getMc()->setDashOn(true);
	            }
                break;

            case SDLK_z :
                stockeur->getMc()->setPushForceH(1);
                break;
            case SDLK_s :
                stockeur->getMc()->setPushForceB(1);
                break;
            case SDLK_q :
                stockeur->getMc()->setPushForceG(1);
                break;
            case SDLK_d :
                stockeur->getMc()->setPushForceD(1);
                break;
			case SDLK_j :
                stockeur->getMc()->getAttack()->updateAttack(1);
				break;
			case SDLK_k :
                stockeur->getMc()->getAttack()->updateAttack(2);
				break;

        }
    }
}

void Input::doKeyUp(SDL_KeyboardEvent &event) {
    switch(event.keysym.sym) {
        case SDLK_ESCAPE :
            exit(0);
        
        case SDLK_SPACE :
            break;

        case SDLK_z :
            stockeur->getMc()->setPushForceH(0);
            break;
        case SDLK_s :
            stockeur->getMc()->setPushForceB(0);
            break;
        case SDLK_q :
            stockeur->getMc()->setPushForceG(0);
            break;
        case SDLK_d :
            stockeur->getMc()->setPushForceD(0);
            break;
        }
}

void Input::mousePress(SDL_MouseButtonEvent& b){
    if(b.button == SDL_BUTTON_LEFT){
        //handle a left-click
        stockeur->getJ2()->newTir(0, mouseX, mouseY);
    }
}

void Input::doOtherKeyDown(SDL_KeyboardEvent &event){
    // Pour un seul press de button
	if (event.repeat == 0)
	{ 
        switch(event.keysym.sym) {
            case SDLK_ESCAPE :
                exit(0);
        }
    }
}