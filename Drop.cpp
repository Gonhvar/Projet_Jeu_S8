#include "Drop.hpp"

/* CONSTRUCTEURS ET DESTRUCTEURS */
Drop::Drop(std::vector<int> items, std::vector<int> taux, int x, int y){
    faction = MC_FACTION;

    std::srand(time(NULL));
    int random = 1 + (rand()%100);
    int rate = 0;
    int i = 0;
    
    masse = 100;
    frottements = 1;
    rayon = 24;

    _coord[0] = x;
    _coord[1] = y -10;

    _largeur = 16;
    _hauteur = 16;
    autoSetHitBox();
    hitBoxType(1, 0);

    // std::cout << "Random : " << random << std::endl; 
    for(int t : taux){
        rate +=t;
        // std::cout << "rate : " << rate << std::endl;
        if(random <= rate){
            item = items[i];
            break;
        }
        i++;
    }

    selectItem();
    stockeur->addItem(this);
}

Drop::~Drop() {
    stockeur->addItem(this);
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

void Drop::update(){
    // std::cout << "Update Item : " << _coord[1] << std::endl;
    addForce(0, sin( 0.008 * SDL_GetTicks()) * 0.3);
    //Detection de prise du joueur à rajouter
}


//Charger ici les textures en fonction de l'item qui spawn
void Drop::selectItem(){
    
    States* newStates = new States(); // newStates est un pointeur temporaire
    item = !item ? 1 : item;
    switch(item){
        case 0 : 
            //Pas d'item
            std::cout << "Creation 0" << std::endl;
            delete this; // Pourquoi ça marche ??????
                        // On supprime l'objet mais la fonction continue de l'utiliser AAAAAAAAAAAAAHHHHHHHHHHH !!!!!!!!!!!!!!!!!!!!!!!
            break;
        
        case 1 : 
            //Un item
            std::cout << "Creation 1" << std::endl;
            newStates->spriteName = "Bonus_degats"; 
            newStates->nbEtats = 1;
            newStates->nbFrameParEtat[0] = 1;
            for (int i=1; i<newStates->nbEtats; i++) {
                newStates->nbFrameParEtat[i] = 0;
            }
            break;

        default :
            break;
    }

    stateRectIn.w = 32;
    stateRectIn.h = 32;
    stateRectIn.x = 0;
    stateRectIn.y = 0;
    stateRect.w = 12;
    stateRect.h = 9;
    
    // stateRect.w = 32;
    // stateRect.h = 32;
    states = newStates;
    onScreen = true;
    
    addSprite("Drop");
    std::cout << "fin creation Item" << std::endl;
}

void Drop::reactionContact(Entite* other) {
    if (other->getFaction() == MC_FACTION) {
        other->getDepForce() *= 1.5;
        markedForDeath = true;
    }
}

//Charger ici les propriété quand le joueur ramasse l'item
void Drop::getItem(){
    switch(item){
        case 1 : 
            break;

        default :
            break;
    }
}