#include "SkeletonShooter.hpp"

const States* SkeletonShooter::etatsSkeletonShooter;

/* CONSTRUCTEURS ET DESTRUCTEURS */
SkeletonShooter::SkeletonShooter() {
    states = SkeletonShooter::etatsSkeletonShooter;
    
    stateRectIn.w = 32;
    stateRectIn.h = 32;
    stateRectIn.x = 0;
    stateRectIn.y = 0;
    stateRect.w = 32;
    stateRect.h = 32;

    addSprite("SkeletonShooter");
}

SkeletonShooter::SkeletonShooter(float _x, float _y) : SkeletonShooter() {
    faction = ENEMY_FACTION;
    PV = 5;
    attackDamage = 1;

    //Selection des drops qu'il pourrait avoir 
    items = {1, 2, 3, 0};
    //Il faut que ça fasse 100% en tout
    taux = {5, 10, 5, 80};

    depForce = BASICSKELETONSHOOTERSPEED;
    _hauteur = 64;
    _largeur = 64;
    
    rayon = 24;
    masse = 7;
    frottements = 50;

    this->setCoord(_x,_y,0);
    onScreen = true;
    maxDelay = 7; // Change de frame tous les 20 ticks

    std::cout << "Création de SkeletonShooter : " << states->spriteName << std::endl;

    autoSetHitBox();
    // addSprite("SkeletonShooter");
}

SkeletonShooter::~SkeletonShooter(){
    std::cout << "Delete SkeletonShooter" << std::endl;
    new Drop(items, taux, _coord[0], _coord[1]);
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

void SkeletonShooter::initialisation() {
	States* newStates = new States(); // newStates est un pointeur temporaire
    newStates->spriteName = "SkeletonShooter"; // Il n'est pas const donc on peut modifier ce qu'il y a à l'adresse
    newStates->nbEtats = 0;
    newStates->nbFrameParEtat[0] = 1;
	SkeletonShooter::etatsSkeletonShooter = newStates;
}



Vector2D SkeletonShooter::deplacementBehaviour(){

    if (currentlyTakingDmg && stockeur->getGameTime() - invicibilityTimeStart > 150) {
        //std::cout << "invicibility ends" << std::endl;
        currentlyTakingDmg = false;
        depForce = BASICSKELETONSHOOTERSPEED;
        //std::cout << "invicibility : " << stockeur->getGameTime() - invicibilityTimeStart << std::endl;
    }

    float deltaX = stockeur->getMc()->getX() - _coord[0];
    float deltaY = stockeur->getMc()->getY() - _coord[1];
    //Si il est trop loin du joueur 
    while(sqrt(deltaX*deltaX + deltaY*deltaY) >= 400){
        //il se téléporte plus proche du joueur
        _coord[0] += deltaX/2;
        _coord[1] += deltaY/2;

        deltaX = stockeur->getMc()->getX() - _coord[0];
        deltaY = stockeur->getMc()->getY() - _coord[1];
    }

    //Calcul de la force que le Enemies veut rajouter
    Vector2D v(deltaX, deltaY);
    move(v);
    // On pousse
    addForce(v);
	return v;
}

void SkeletonShooter::attackBehaviour(){
    if(stockeur->getGameTime() - startShooting > cooldown){
        // std::cout << "Creation bullet SkeletonShooter" << std::endl;
        stockeur->addBullets(new Bullets(0, stockeur->getMc()->getX() - _coord[0], stockeur->getMc()->getY() -_coord[1], this, ENEMY_BULLET_FACTION));
        startShooting = stockeur->getGameTime();
    }
}

void SkeletonShooter::takingDamage(Entite* other){
    if(other->getFaction() != ENEMY_FACTION){
        if(!currentlyTakingDmg){
            //std::cout << "il se prend des dmg" << std::endl;
            changePV(other->getAttackDmg());
            currentlyTakingDmg = true;
            depForce *= knockback;
            invicibilityTimeStart = stockeur->getGameTime();
        }
    }
}

void SkeletonShooter::reactionContact(Entite* other) {
    if (Sprite::stockeur->printEverything) {
		std::cout << "Contact SkeletonShooter : " << this << "(" << states->spriteName << ")" << " ->" << other << std::endl;
	}
    if (faction != other->getFaction()) {
        stockeur->getAudioManager()->playSound("punch");
        other->changePV(attackDamage);
	}
}





// Fonctions de sauvegarde de l'objet
std::string SkeletonShooter::serialize(std::string& toWrite) {
	Enemies::serialize(toWrite);
	// On n'enregistre que les paramètres nécessaires. Certains constructeur renseignent déjà les autres 
    // Ces paramètres nécessaires sont en fait les paramètres contextuels (susceptibles de changer à chaque instant)
	std::ostringstream oss;
    oss << knockback << "|" << cooldown << "|" << startShooting << "|";
    toWrite += oss.str();
    return "SkeletonShooter";
}

std::istringstream& SkeletonShooter::deSerialize(std::istringstream& iss) {
    Enemies::deSerialize(iss);
    std::string token;
    if (std::getline(iss, token, '|')) {
        knockback = std::stof(token);
    }
    if (std::getline(iss, token, '|')) {
        cooldown = std::stoul(token);
    }
    if (std::getline(iss, token, '|')) {
        startShooting = std::stoul(token);
    }
	return iss;
}