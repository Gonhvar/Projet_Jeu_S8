#include "Drop.hpp"

Drop::Drop(std::vector<int> items, std::vector<int> taux, int x, int y){

    std::srand(time(NULL));
    int random = 1 + (rand()%100);
    int rate = 0;
    int i = 0;
    
    masse = 1;
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

void Drop::update(){
    // std::cout << "Update Item : " << _coord[1] << std::endl;
    addForce(0, sin( 0.008 * SDL_GetTicks()) * 0.3);
    //Detection de prise du joueur à rajouter
}


//Charger ici les textures en fonction de l'item qui spawn
void Drop::selectItem(){
    
    States* newStates = new States(); // newStates est un pointeur temporaire

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
            newStates->spriteName = "Item1"; 
            newStates->nbEtats = 1;
            newStates->nbFrameParEtat[0] = 1;
            for (int i=1; i<newStates->nbEtats; i++) {
                newStates->nbFrameParEtat[i] = 0;
            }
            break;

        default :
            break;
    }
    stateRect.w = 16;
    stateRect.h = 16;
    states = newStates;
    onScreen = true;
    
    addSprite();
    std::cout << "fin creation Item" << std::endl;
}

void Drop::reactionContact(Entite* other) {
    other->getDepForce() += 200;
    markedForDeath = true;
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