#include "BasicSkeleton.hpp"


BasicSkeleton::BasicSkeleton(float _x, float _y) {
    faction = ENEMY_FACTION;
    PV = 10;
    attackDamage = 5;

    //Selection des drops qu'il pourrait avoir 
    items = {0, 1};
    //Il faut que ça fasse 100% en tout
    taux = {20, 80};

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


    stateRectIn.w = 32;
    stateRectIn.h = 32;
    stateRectIn.x = 0;
    stateRectIn.y = 0;
    stateRect.w = 32;
    stateRect.h = 32;

    // stateRect.w = 32;
    // stateRect.h = 32;

    std::cout << "Création de BasicSkeleton : " << states->spriteName << std::endl;

    autoSetHitBox();
    addSprite("BasicSkeleton");
}

BasicSkeleton::~BasicSkeleton(){
    std::cout << "Delete BasicSkeleton" << std::endl;
    new Drop(items, taux, _coord[0], _coord[1]);
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

    // On pousse
    addForce(v);
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
    if (Sprite::stockeur->printEverything) {
		std::cout << "Contact BasicSkeleton : " << this << "(" << states->spriteName << ")" << " ->" << other << std::endl;
	}
    if (faction != other->getFaction()) {
        other->changePV(1);
	}
}
