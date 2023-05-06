#include "BasicSkeleton.hpp"

BasicSkeleton::BasicSkeleton(float _x, float _y) {
    PV = 10;
    vitesse = 30.0;
    _hauteur = 64;
    _largeur = 48;
    
    rayon = 24;

    this->setCoord(_x,_y,0);
    this->setOnScreen(true);

    states = &(etatsDesBasicSkeleton);

    std::cout << "Création de BasicSkeleton : " << states->spriteName << std::endl;

    autoSetHitBox();
    addSprite();
}

void BasicSkeleton::deplacementBehaviour(){
    //Test si le skeleton prend des dégats
    takingDamage();

    //Faire le test des hitbox maitenant
    //Calcul du déplacement à réaliser
    Vector2D v(joueur->getX() - _coord[0], joueur->getY() - _coord[1]);

    //Test si déplacement*vitesse touche le joueur avant de le réaliser
    translate(moveCollisionCercle(static_cast<Entite*>(joueur), move(v)));
}

void BasicSkeleton::attackBehaviour(){

}

void BasicSkeleton::takingDamage(){
     
}