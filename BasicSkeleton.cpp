#include "BasicSkeleton.hpp"

BasicSkeleton::BasicSkeleton(float _x, float _y) {
    PV = 10;
    vitesse = 30.0;
    _hauteur = 64;
    _largeur = 48;

    this->setCoord(_x,_y,0);
    this->setOnScreen(true);

    states = &(etatsDesBasicSkeleton);

    std::cout << "Création de BasicSkeleton : " << states->spriteName << std::endl;

    addSprite();
}

void BasicSkeleton::deplacementBehaviour(){

    //Déplacement de base pour voir si tout fonctionne (rajouter de l'inertie)
/*    if(joueur->getX() < _coord[0]){
        dx = -vitesse;
    }else{
        dx = vitesse;
    }
    if(joueur->getY() < _coord[1]){
        dy = -vitesse;
    }else{
        dy = vitesse;
    }
*/
    //Faire le test des hitbox maitenant 
    move((joueur->getX() - _coord[0]), (joueur->getY() - _coord[1]));
}

void BasicSkeleton::attackBehaviour(){

}