#include "Input.hpp"
#include "Menu.hpp"

const States* Input::etatsInput;

/* CONSTRUCTEURS ET DESTRUCTEURS */
Input::Input(){
	//std::cout <<"CREATION INPUT" << std::endl;
    stockeur->setInputLoaded(true);
	dashValue = stockeur->getMc()->getDashValue();

	_hauteur = 32;
    _largeur = 32;
    // std::cout << "Creation Input" << std::endl;

    stateRectIn.w = 16;
    stateRectIn.h = 16;
    stateRectIn.x = 0;
    stateRectIn.y = 0;
    stateRect.w = 11;
    stateRect.h = 11;

    states = Input::etatsInput;
		
	onScreen = true;
	addSprite("Input");
    controleList.resize(1);
}

Input::~Input() {
    std::cout << "delete Input" << std::endl;
    stockeur->setInputLoaded(false);
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

void Input::initialisation() {
	States* newStates = new States(); // newStates est un pointeur temporaire
    newStates->spriteName = "Viseur"; //Mettre un viseur 
    newStates->nbEtats = 1;
    newStates->nbFrameParEtat[0] = 1;
    for (int i=1; i<newStates->nbEtats; i++) {
        newStates->nbFrameParEtat[i] = 0;
    }
	Input::etatsInput = newStates;
}


void Input::update(){
    SDL_GetMouseState(&mouseX, &mouseY);
    _coord[0] = Sprite::afficheur->getCameraX() + mouseX / Sprite::afficheur->getZoom();
    _coord[1] = Sprite::afficheur->getCameraY() + mouseY / Sprite::afficheur->getZoom();
    mouseX = _coord[0];
    mouseY = _coord[1];

    switch(Sprite::mode){
        case (MODE_JEU) :
            get_keypress();
            break;
        
        case (MODE_PAUSE) :
            get_pauseKeypress();
            break;

        default :
            break;
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

void Input::doKeyDown(SDL_KeyboardEvent &event){   
    // Pour un seul press de button
	if (event.repeat == 0)
	{ 
        switch(event.keysym.sym) {
            case SDLK_ESCAPE :
                std::cout << "menu swap" << std::endl;
                Sprite::mode = MODE_PAUSE;
                Sprite::stockeur->getMenu()->setOnScreen(true);
                break;

            case SDLK_SPACE :
                if( !(stockeur->getMc()->getDashOn())){
                    stockeur->getAudioManager()->playSound("dash_sound");
                    stockeur->getMc()->getDepForce() *= dashValue;
                    stockeur->getMc()->setStartDashTime(stockeur->getGameTime());
                    stockeur->getMc()->setDashOn(true);
	            }
                break;

            case SDLK_z :
                // std::cout << "z key down" << std::endl;
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
                stockeur->getMc()->getAttacks()->updateAttack(1);
				break;
			case SDLK_k :
                stockeur->getMc()->getAttacks()->updateAttack(2);
				break;

            case SDLK_n :
                stockeur->deleteAllEnemies();
				break;

            case SDLK_EQUALS : // Zoom de 10% sur l'image
                Sprite::afficheur->zoomPlus();
                break;

            case SDLK_RIGHTPAREN : // Dezoom de 10% sur l'image
                Sprite::afficheur->zoomMoins();
                break;

        }
    }
}

void Input::doKeyUp(SDL_KeyboardEvent &event) {
    switch(event.keysym.sym) {   
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


void Input::get_pauseKeypress(){
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {   
        switch(event.type){
            case SDL_KEYDOWN :
                doPauseKeyDown(event.key);
            default : break;
        }
    }
}

void Input::doPauseKeyDown(SDL_KeyboardEvent &event){
    if (event.repeat == 0)
	{ 
        switch(event.keysym.sym) {
            case SDLK_ESCAPE :
                Sprite::mode = MODE_JEU;
                Sprite::stockeur->getMenu()->setOnScreen(false);
                break;

            case SDLK_z :
                stockeur->getMenu()->addToEtat(-1);
                break;

            case SDLK_s :
                stockeur->getMenu()->addToEtat(1);
                break;

            case SDLK_e :
                stockeur->getMenu()->select();
                break;
        }
    }
    this->mouseX += 1;
    std::cout << "fin doPauseKeyDown Input :" << this->mouseX << std::endl;
}

void Input::addMe(Controle* toAdd) {
    controleList.push_back(toAdd);
}





// Fonctions de sauvegarde de l'objet (l'objet ne doit pas être enregistré)
std::string Input::serialize(std::string& toWrite) {
    return DONT_SERIALIZE_ME;
}

std::istringstream& Input::deSerialize(std::istringstream& iss) {
	return iss;
}