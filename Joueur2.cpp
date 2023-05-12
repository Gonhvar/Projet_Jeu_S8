#include "Joueur2.hpp"

Joueur2::Joueur2(){

    Sprite::joueur2 = this;

    _hauteur = 16;
    _largeur = 16;

    setCoord(joueur->getX(),joueur->getY(),0);

    setOnScreen(true);

    states = &(etatsDeJoueur2);
    addSprite();
    //std::cout << "Creation" << std::endl;
}


void Joueur2::update(){
    //std::cout << "uPDATE" << std::endl;

    SDL_GetMouseState(&mouseX, &mouseY);

    //Mettre un effet de ressorts autour de ce point
    deplacementDynamique();

    
}

void Joueur2::deplacementDynamique() {
    vitesseActuelle[0] += k*((joueur->getX()+DECALAGE_J2) - _coord[0]) - frottement*vitesseActuelle[0];
    vitesseActuelle[1] += k*((joueur->getY()-DECALAGE_J2) - _coord[1]) - frottement*vitesseActuelle[1];

    _coord[0] += vitesseActuelle[0];
    _coord[1] += vitesseActuelle[1];
}
