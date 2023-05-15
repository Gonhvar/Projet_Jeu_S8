#include "BasicSkeleton.hpp"

BasicSkeleton::BasicSkeleton(float _x, float _y) {
    PV = 10;
    attackDamage = 5;

    vitesse = BASICSKELETONSPEED;
    _hauteur = 64;
    _largeur = 48;
    
    rayon = 24;
    masse = 10;

    this->setCoord(_x,_y,0);
    onScreen = true;

    states = &(etatsDesBasicSkeleton);

    std::cout << "Création de BasicSkeleton : " << states->spriteName << std::endl;

    autoSetHitBox();
    
    addSprite();
}

void BasicSkeleton::deplacementBehaviour(){

    if(!currentlyTakingDmg){
        //Calcul du déplacement à réaliser
        Vector2D v(joueur->getX() - _coord[0], joueur->getY() - _coord[1]);
        moveAllCollision(move(v));
        translate(v);
    }
    else{
        Vector2D v(_coord[0] - joueur->getX(), _coord[1] - joueur->getY());
        
        if(SDL_GetTicks() - invicibilityTimeStart > 150){
            //std::cout << "invicibility ends" << std::endl;
            currentlyTakingDmg = false;
            vitesse = BASICSKELETONSPEED;
            //std::cout << "invicibility : " << SDL_GetTicks() - invicibilityTimeStart << std::endl;
        }
        moveAllCollision(move(v));
        translate(v);
    }
}

void BasicSkeleton::attackBehaviour(){

}

void BasicSkeleton::takingDamage(Entite* other){
    if(!currentlyTakingDmg){
        //std::cout << "il se prend des dmg" << std::endl;
        changePV(other->getAttackDmg());
        currentlyTakingDmg = true;
        vitesse *= knockback;
        invicibilityTimeStart = SDL_GetTicks();
    }
}