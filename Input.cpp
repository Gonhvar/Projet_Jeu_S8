#include "Input.hpp"

/* CONSTRUCTEURS ET DESTRUCTEURS */
Input::Input(){
	//std::cout <<"CREATION INPUT" << std::endl;
	_mc = stockeur->getMc();

	dashValue = _mc->getDashValue();

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

    get_keypress();
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

void Input::doKeyDown(SDL_KeyboardEvent &event)
{   
    // Pour un seul press de button
	if (event.repeat == 0)
	{ 
        switch(event.keysym.sym) {
            case SDLK_ESCAPE :
                exit(0);
            
            case SDLK_SPACE :
                if( !(_mc->getDashOn()) ){
                    _mc->getDepForce() *= dashValue;
                    _mc->setStartDashTime(SDL_GetTicks());
                    _mc->setDashOn(true);
	            }
                break;

            case SDLK_z :
                _mc->setPushForceH(1);
                break;
            case SDLK_s :
                 _mc->setPushForceB(1);
                break;
            case SDLK_q :
                 _mc->setPushForceG(1);
                break;
            case SDLK_d :
                 _mc->setPushForceD(1);
                break;
			case SDLK_j :
				_mc->getAttack()->updateAttack(1);
				break;
			case SDLK_k :
				_mc->getAttack()->updateAttack(2);
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
            _mc->setPushForceH(0);
            break;
        case SDLK_s :
            _mc->setPushForceB(0);
            break;
        case SDLK_q :
            _mc->setPushForceG(0);
            break;
        case SDLK_d :
            _mc->setPushForceD(0);
            break;
        }
}

void Input::mousePress(SDL_MouseButtonEvent& b){
    if(b.button == SDL_BUTTON_LEFT){
        //handle a left-click
        stockeur->getJ2()->newTir(0, mouseX, mouseY);
    }
}