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
    _coord[0]= (joueur->getX()+20);
    _coord[1]= (joueur->getY()-20);


    
}

