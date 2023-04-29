#include "BasicSkeleton.hpp"

BasicSkeleton::BasicSkeleton(float _x, float _y) {
    PV = 10;
    vitesse = 30.0;
    _hauteur = 64;
    _largeur = 48;

    this->setCoord(_x,_y,0);
    this->setOnScreen(true);

    states = &(etatsDesBasicSkeleton);
    addSprite();
}

void BasicSkeleton::Initialisation() {

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
    float ux = (joueur->getX() - _coord[0]);
    float uy = (joueur->getY() - _coord[1]);
    double norme = 0.5*sqrt(ux*ux + uy*uy);
    ux /= norme;
    uy /= norme;

    dx = ux * vitesse;
    dy = uy * vitesse;

    //Faire le test des hitbox maitenant 
    this->translate(dx, dy);
}

void BasicSkeleton::attackBehaviour(){

}