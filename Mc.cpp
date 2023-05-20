#include "Mc.hpp"

/* CONSTRUCTEURS ET DESTRUCTEURS */

//Constructeur spécial pour le MC (renseigne Sprite::joueur)
Mc::Mc() {
    //On donne en référence le joueur pour l'utiliser plus tard
    Sprite::joueur = this;
    
    PV = 20;
    PVMax = PV;

    depForce = BASICSPEED;
    dashValue = 4.0;

    _hauteur = 64;
    _largeur = 48;
    rayon = 24;
    masse = 20;
    frottements = 350;

    _coord[0] = 200;
    _coord[1] = 200;

    this->setCoord(10,20,0);
    onScreen = true;
    
    //states = &(etatsDesMc);
		States* newStates = new States(); // newStates est un pointeur temporaire
		newStates->spriteName = "Robot"; // Il n'est pas const donc on peut modifier ce qu'il y a à l'adresse
		newStates->nbEtats = 1;
		newStates->nbFrameParEtat[0] = 1;
		for (int i=1; i<newStates->nbEtats; i++) {
			newStates->nbFrameParEtat[i] = 0;
		}
		states = newStates;
        
    maxDelay = 20; // Change de frame tous les 20 ticks

    speed.redef(0,0);

    autoSetHitBox();
    addSprite();
    attack = new Attacks(this);
    //std::cout << "Création de Mc : " << states->spriteName << std::endl;
}

Mc::~Mc() {
    delete attack;
    Sprite::joueur = nullptr;
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

void Mc::update() {

    if(dashOn){
        //Regarde si le temps de dash est fini (bloque les autres mouvement)
        actualDashTime = SDL_GetTicks() - startDashTime;
        //std::cout << actualDashTime << std::endl;
        if(actualDashTime > 1000/dashValue){
            dashOn = false;
            depForce = BASICSPEED;

            //Faire un CD entre plusieurs dash ici
        }
    }

    //faire test de direction ici;
    attack->update(pushForceH, pushForceB, pushForceG, pushForceD);

    //Calcul de la force que le MC veut rajouter
    Vector2D v(pushForceD - pushForceG, pushForceB - pushForceH);
    move(v);

    // On change la vitesse actuelle du Mc en fonction des forces appliquées sur lui et des collisions
    accelerateWithForce(v.x, v.y);
    
    // Les collisions dépendent des itérations de déplacement
    Killable::updateSpeedWithCollisions();

    translate(speed);
}


void Mc::setPushForceH(int n){
    pushForceH = n;
}

void Mc::setPushForceB(int n){
    pushForceB = n;
}

void Mc::setPushForceG(int n){
    pushForceG = n;
}

void Mc::setPushForceD(int n){
    pushForceD = n;
}

void Mc::setDashOn(bool n){
    dashOn = n;
}

void Mc::setStartDashTime(uint32_t time){
    startDashTime = time;
}

float& Mc::getDashValue(){
    return dashValue;
}

bool Mc::getDashOn(){
    return dashOn;
}

Attacks* Mc::getAttack(){
    return attack;
}
