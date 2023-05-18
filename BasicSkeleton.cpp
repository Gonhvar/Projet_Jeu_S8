#include "BasicSkeleton.hpp"

BasicSkeleton::BasicSkeleton(float _x, float _y) {
    PV = 10;
    attackDamage = 5;

    depForce = BASICSKELETONSPEED;
    _hauteur = 64;
    _largeur = 48;
    
    rayon = 24;
    masse = 7;
    frottements = 50;

    this->setCoord(_x,_y,0);
    onScreen = true;

    states = &(etatsDesBasicSkeleton);

    std::cout << "Création de BasicSkeleton : " << states->spriteName << std::endl;

    autoSetHitBox();
    
    addSprite();
}

void BasicSkeleton::deplacementBehaviour(){

    if (currentlyTakingDmg && SDL_GetTicks() - invicibilityTimeStart > 150) {
        //std::cout << "invicibility ends" << std::endl;
        currentlyTakingDmg = false;
        depForce = BASICSKELETONSPEED;
        //std::cout << "invicibility : " << SDL_GetTicks() - invicibilityTimeStart << std::endl;
    }

    //Calcul de la force que le Enemies veut rajouter
    Vector2D v(joueur->getX() - _coord[0], joueur->getY() - _coord[1]);
    move(v);

    // On change la vitesse actuelle du Mc en fonction des forces appliquées sur lui et des collisions
    accelerateWithForce(v.x, v.y);
    
    // Les collisions dépendent des itérations de déplacement
    Killable::updateSpeedWithCollisions();

    translate(speed);
}

void BasicSkeleton::attackBehaviour(){

}

void BasicSkeleton::takingDamage(Entite* other){
    if(!currentlyTakingDmg){
        //std::cout << "il se prend des dmg" << std::endl;
        changePV(other->getAttackDmg());
        currentlyTakingDmg = true;
        depForce *= knockback;
        invicibilityTimeStart = SDL_GetTicks();
    }
}