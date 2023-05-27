#include "BasicSkeleton.hpp"


BasicSkeleton::BasicSkeleton(float _x, float _y) {
    PV = 10;
    attackDamage = 5;

    depForce = BASICSKELETONSPEED;
    _hauteur = 64;
    _largeur = 64;
    
    rayon = 24;
    masse = 7;
    frottements = 50;

    this->setCoord(_x,_y,0);
    onScreen = true;

    //states = &(etatsDesBasicSkeleton);
		States* newStates = new States(); // newStates est un pointeur temporaire
		newStates->spriteName = "BasicSkeleton"; // Il n'est pas const donc on peut modifier ce qu'il y a à l'adresse
		newStates->nbEtats = 4;
		newStates->nbFrameParEtat[0] = 2;
		newStates->nbFrameParEtat[1] = 2;
		newStates->nbFrameParEtat[2] = 2;
		newStates->nbFrameParEtat[3] = 2;
		newStates->nbFrameParEtat[4] = 0;
		newStates->nbFrameParEtat[5] = 0;
		newStates->nbFrameParEtat[6] = 0;
		newStates->nbFrameParEtat[7] = 0;
		newStates->nbFrameParEtat[8] = 0;
		newStates->nbFrameParEtat[9] = 0;

		states = newStates;
    maxDelay = 7; // Change de frame tous les 20 ticks

    stateRect.w = 32;
    stateRect.h = 32;

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
    Vector2D v(stockeur->getMc()->getX() - _coord[0], stockeur->getMc()->getY() - _coord[1]);
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

void BasicSkeleton::reactionContact(Entite* other) {
    other->changePV(1);
}
