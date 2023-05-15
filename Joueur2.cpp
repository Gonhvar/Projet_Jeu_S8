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
    //Mettre un effet de ressorts autour de ce point
    deplacementDynamique();

    for(Bullets* bullet : bullets){
        bullet->update();
    }
}

void Joueur2::deplacementDynamique() {
    vitesseActuelle[0] += k*((joueur->getX()+DECALAGE_J2) - _coord[0]) - frottement*vitesseActuelle[0];
    vitesseActuelle[1] += k*((joueur->getY()-DECALAGE_J2) - _coord[1]) - frottement*vitesseActuelle[1];

    _coord[0] += vitesseActuelle[0];
    _coord[1] += vitesseActuelle[1];
}

void Joueur2::newTir(int state, int directX, int directY){
    
    std::cout << "creation bullets" << std::endl;
    //std::cout << "Alors X : " << x - _coord[0] << " Y :" << y - _coord[0] << std::endl;
    bullets.push_back(new Bullets(0, directX-_coord[0], directY-_coord[1]));
}