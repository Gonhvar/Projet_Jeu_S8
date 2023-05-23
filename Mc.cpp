#include "Mc.hpp"

uint8_t tabState[3][3][2] = { // Représente l'état et le flip en fonction de la direction dans laquelle on pousse
	{{3,1}, {5,0}, {3,0}},
	{{3,1}, {0,0}, {3,0}},
	{{3,1}, {4,0}, {3,0}}
};

uint8_t stateTranslator[6] = {2, 1, 4, 0, 3, 4}; // On utilise ce tableau pour "remettre dans l'ordre" les sprite de la sprite sheet


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
		newStates->nbEtats = 6;
		newStates->nbFrameParEtat[0] = 2;
		newStates->nbFrameParEtat[1] = 2;
		newStates->nbFrameParEtat[2] = 2;
		newStates->nbFrameParEtat[3] = 2;
		newStates->nbFrameParEtat[4] = 2;
		newStates->nbFrameParEtat[5] = 2;
		newStates->nbFrameParEtat[6] = 0;
		newStates->nbFrameParEtat[7] = 0;
		newStates->nbFrameParEtat[8] = 0;
		newStates->nbFrameParEtat[9] = 0;

		states = newStates;
        
    maxDelay = 7; // Change de frame tous les 4 ticks

    stateRect.w = 32;
    stateRect.h = 32;

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

    //Décision de l'état
    if (dashOn) {
        std::cout << "dash" << std::endl;
        setEtat(5);
    }
    else {
        // Cette façon de faire est rapide mais ne marche que si les pushForce restent binaires
        // A priori, il ne devrait pas y avoir de raison de sortir les pushForce d'un spectr binaire
        // Calcul de l'état actuel à partir du déplacement
        int X = pushForceD - pushForceG;
        int Y = pushForceB - pushForceH;
        int newEtat;
        if (!X && !Y) { // On ne pousse pas
            newEtat = etat%3;
            newEtat = stateTranslator[newEtat];
            maxDelay = 14; // Donne un air plus détendu à l'arrêt
            // std::cout << "X :" << X << ", Y :" << Y << std::endl;
            // std::cout << "etat :" << newEtat << ", flip :" << flip << std::endl;
        }
        else {
            newEtat = tabState[Y+1][X+1][0];
            flip = tabState[Y+1][X+1][1];
            newEtat = stateTranslator[newEtat];
            maxDelay = 7;
            // std::cout << "X :" << X << ", Y :" << Y << std::endl;
            // std::cout << "etat :" << newEtat << ", flip :" << flip << std::endl;
        }
        if (newEtat != etat) {
            setEtat(newEtat);
        }
    }


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
