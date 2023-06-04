#include "BasicSkeleton.hpp"

const States* BasicSkeleton::etatsBasicSkeleton;

/* CONSTRUCTEURS ET DESTRUCTEURS */
BasicSkeleton::BasicSkeleton() {    
    states = etatsBasicSkeleton;

    stateRectIn.w = 32;
    stateRectIn.h = 32;
    stateRectIn.x = 0;
    stateRectIn.y = 0;
    stateRect.w = 32;
    stateRect.h = 32;

    addSprite("BasicSkeleton");
}

BasicSkeleton::BasicSkeleton(float _x, float _y) : BasicSkeleton() {
    faction = ENEMY_FACTION;
    PV = 10;
    attackDamage = 2;

    //Selection des drops qu'il pourrait avoir 
    items = {1, 2, 3, 0};
    //Il faut que ça fasse 100% en tout
    taux = {5, 5, 5, 75};

    depForce = BASICSKELETONSPEED;
    _hauteur = 64;
    _largeur = 64;
    
    rayon = 24;
    masse = 7;
    frottements = 50;

    this->setCoord(_x,_y,0);
    onScreen = true;

    maxDelay = 7; // Change de frame tous les 20 ticks

    // std::cout << "Création de BasicSkeleton : " << states->spriteName << std::endl;

    autoSetHitBox();
}

BasicSkeleton::~BasicSkeleton(){
    // std::cout << "Delete BasicSkeleton" << std::endl;
    new Drop(items, taux, _coord[0], _coord[1]);
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

void BasicSkeleton::initialisation() {
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
	BasicSkeleton::etatsBasicSkeleton = newStates;
}


Vector2D BasicSkeleton::deplacementBehaviour(){

    if (currentlyTakingDmg && stockeur->getGameTime() - invicibilityTimeStart > 150) {
        //std::cout << "invicibility ends" << std::endl;
        currentlyTakingDmg = false;
        depForce = BASICSKELETONSPEED;
        //std::cout << "invicibility : " << stockeur->getGameTime() - invicibilityTimeStart << std::endl;
    }

    //Calcul de la force que le Enemies veut rajouter
    Vector2D v(stockeur->getMc()->getX() - _coord[0], stockeur->getMc()->getY() - _coord[1]);
    move(v);

    // On pousse
    addForce(v);
	return v;
}

void BasicSkeleton::attackBehaviour(){

}

void BasicSkeleton::takingDamage(Entite* other){
    if(other->getFaction() != ENEMY_FACTION){
        if(!currentlyTakingDmg){
            //std::cout << "il se prend des dmg" << std::endl;
            changePV(other->getAttackDmg());
            std::cout << "Attack Dmg" << other->getAttackDmg() << std::endl;
            currentlyTakingDmg = true;
            depForce *= knockback;
            invicibilityTimeStart = stockeur->getGameTime();
        }
    }
}

void BasicSkeleton::reactionContact(Entite* other) {
    if (Sprite::stockeur->printEverything) {
		std::cout << "Contact BasicSkeleton : " << this << "(" << states->spriteName << ")" << " ->" << other << std::endl;
	}
    if (faction != other->getFaction()) {
        stockeur->getAudioManager()->playSound("punch");
        other->changePV(attackDamage);
	}
}





// Fonctions de sauvegarde de l'objet
std::string BasicSkeleton::serialize(std::string& toWrite) {
	Enemies::serialize(toWrite);
	// On n'enregistre que les paramètres nécessaires. Certains constructeur renseignent déjà les autres 
    // Ces paramètres nécessaires sont en fait les paramètres contextuels (susceptibles de changer à chaque instant)
	std::ostringstream oss;
    oss << knockback << "|";
    toWrite += oss.str();
    return "BasicSkeleton";
}

std::istringstream& BasicSkeleton::deSerialize(std::istringstream& iss) {
    Enemies::deSerialize(iss);
    std::string token;
    if (std::getline(iss, token, '|')) {
        knockback = std::stof(token);
    }
	return iss;
}