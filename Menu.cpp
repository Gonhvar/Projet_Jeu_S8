#include "Menu.hpp"
#include "Input.hpp"

const States* Menu::etatsMenu;

/* CONSTRUCTEURS ET DESTRUCTEURS */
Menu::Menu(){
    _hauteur = 80;
    _largeur = 59;

    stateRectIn.w = 80;
    stateRectIn.h = 45;
    stateRectIn.x = 0;
    stateRectIn.y = 0;
    stateRect.w = 80;
    stateRect.h = 45;

    states = Menu::etatsMenu;

    onScreen = false;
    etat = 0;
    max_menu = 5;
    // std::cout << "Creation Menu" << std::endl;   
    addSprite("Menu");
    Sprite::stockeur->removeSprites(this);
}

void Menu::initialisation() {
	States* newStates = new States(); // newStates est un pointeur temporaire
    newStates->spriteName = "Menu_Pause";  
    newStates->nbEtats = 5;
    newStates->nbFrameParEtat[0] = 1;
    newStates->nbFrameParEtat[1] = 1;
    newStates->nbFrameParEtat[2] = 1;
    newStates->nbFrameParEtat[3] = 1;
    newStates->nbFrameParEtat[4] = 1;
    for (int i=5; i<newStates->nbEtats; i++) {
        newStates->nbFrameParEtat[i] = 0;
    }
	Menu::etatsMenu = newStates;
}

void Menu::update(){
    switch(Sprite::mode){
        case MODE_PAUSE :

            break;
        
        default :
            break;
    }
}


void Menu::addToEtat(int e){
    etat += e;
    etat = etat%max_menu;
    etat = etat < 0 ?  max_menu-1 : etat;

    setEtat(etat);
}

void Menu::select() {
    switch (etat) {
        case 0 : // reprendre
            Sprite::mode = MODE_JEU;
            onScreen = false;
			break;
        case 1 : // créer
            Sprite::mode = MODE_MAP;
            onScreen = false;
			break;
        case 2 : // sauver
            stockeur->saveGame();
            etat = 0;
			break;
        case 3 : // charger
            // Sprite::mode = MODE_LOADING;
            std::cout << "MODE_LOADING abandonné faute de temps" << std::endl;
			break;
        case 4 : // quitter
            exit(0);
    }
}



// Fonctions de sauvegarde de l'objet (l'objet ne doit pas être enregistré)
std::string Menu::serialize(std::string& toWrite) {
    return DONT_SERIALIZE_ME;
}

std::istringstream& Menu::deSerialize(std::istringstream& iss) {
	return iss;
}