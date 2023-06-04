#include "Menu.hpp"

const States* Menu::etatsMenu;

/* CONSTRUCTEURS ET DESTRUCTEURS */
Menu::Menu(){
    _hauteur = 80;
    _largeur = 59;

    stateRectIn.w = 80;
    stateRectIn.h = 59;
    stateRectIn.x = 0;
    stateRectIn.y = 0;
    stateRect.w = 11;
    stateRect.h = 11;

    states = Menu::etatsMenu;

    onScreen = false;
    etat = 0;
    mode = MODE_JEU;
    max_menu = 3;
    // std::cout << "Creation Menu" << std::endl;   
    addSprite("Menu");
}

void Menu::initialisation() {
	States* newStates = new States(); // newStates est un pointeur temporaire
    newStates->spriteName = "Main_menu_Sheet";  
    newStates->nbEtats = 1;
    newStates->nbFrameParEtat[0] = 1;
    for (int i=1; i<newStates->nbEtats; i++) {
        newStates->nbFrameParEtat[i] = 0;
    }
	Menu::etatsMenu = newStates;
}

void Menu::update(){
    switch(mode){
        case MODE_MENU :
    
            break;

        case MODE_PAUSE :

            break;
        
        default :
            break;
    }
}


void Menu::setMode(int m){
    mode = m;

    switch(mode){
        case MODE_MENU :
            max_menu = 3;
            break;

        case MODE_PAUSE :
            max_menu = 2;
            break;
        
        default :
            break;
    }
}


void Menu::addToEtat(int e){
    etat += e;

    if(etat < 0){
        etat = max_menu;
    }

    etat = etat%max_menu;
}





// Fonctions de sauvegarde de l'objet (l'objet ne doit pas être enregistré)
std::string Menu::serialize(std::string& toWrite) {
    return DONT_SERIALIZE_ME;
}

std::istringstream& Menu::deSerialize(std::istringstream& iss) {
	return iss;
}