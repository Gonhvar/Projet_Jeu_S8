#include "Mc.hpp"

uint8_t tabState[3][3][2] = { // Représente l'état et le flip en fonction de la direction dans laquelle on pousse
	{{3,1}, {5,0}, {3,0}},
	{{3,1}, {0,0}, {3,0}},
	{{3,1}, {4,0}, {3,0}}
};

/* CONSTRUCTEURS ET DESTRUCTEURS */

//Constructeur spécial pour le MC (renseigne Sprite::joueur)
Mc::Mc() {
    faction = MC_FACTION;
    
    PV = 20;
    PVMax = PV;

    depForce = BASICSPEED;
    dashValue = 4.0;

    _hauteur = 64;
    _largeur = 64;
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
		newStates->nbEtats = 9;
		newStates->nbFrameParEtat[0] = 2;
		newStates->nbFrameParEtat[1] = 2;
		newStates->nbFrameParEtat[2] = 2;
		newStates->nbFrameParEtat[3] = 2;
		newStates->nbFrameParEtat[4] = 2;
		newStates->nbFrameParEtat[5] = 2;
		newStates->nbFrameParEtat[6] = 2;
		newStates->nbFrameParEtat[7] = 2;
		newStates->nbFrameParEtat[8] = 2;
		newStates->nbFrameParEtat[9] = 0;

		states = newStates;
    addSprite("Mc");
        
    maxDelay = 7; // Change de frame tous les 4 ticks


    stateRectIn.w = 32;
    stateRectIn.h = 32;
    stateRectIn.x = 0;
    stateRectIn.y = 0;
    stateRect.w = 32;
    stateRect.h = 32;

    std::cout <<"Mc rect : " << getRightRectangle()->x << ", " << getRightRectangle()->y << std::endl;

    autoSetHitBox();
    hitBoxType(1, 0);
    
    color = NONE;
    attack = new Attacks();
    //std::cout << "Création de Mc : " << states->spriteName << std::endl;
}

Mc::~Mc() {
    std::cout << "Delete Mc" << std::endl;
    delete stockeur->getJ2();
    delete attack;

    stockeur->addMc(nullptr);
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

void Mc::update() {
    // std::cout << "Checkpoint" << std::endl;
    if (Sprite::stockeur->printEverything) {
        std::cout << "MC::update()" << std::endl;
    }
    // std::cout << "Checkpoint2" << std::endl;
    if(dashOn){
        //Regarde si le temps de dash est fini (bloque les autres mouvement)
        actualDashTime = SDL_GetTicks() - startDashTime;
        //std::cout << actualDashTime << std::endl;
        if(actualDashTime > 1000/dashValue){
            dashOn = false;
            depForce = dashValue ? depForce/dashValue : BASICSPEED;
            //Faire un CD entre plusieurs dash ici
        }
    }

    //faire test de direction ici;
    attack->update(pushForceH, pushForceB, pushForceG, pushForceD);

    //Décision de l'état
    int newEtat;
    if (dashOn) { // dash
        newEtat = etat%3 +6;
    }
    else {
        // Cette façon de faire est rapide mais ne marche que si les pushForce restent binaires
        // A priori, il ne devrait pas y avoir de raison de sortir les pushForce d'un spectre binaire
        // Calcul de l'état actuel à partir du déplacement
        int X = pushForceD - pushForceG;
        int Y = pushForceB - pushForceH;
        if (!X && !Y) { // Ne pousse pas
            newEtat = etat%3;
            maxDelay = 14; // Donne un air plus détendu à l'arrêt
            // std::cout << "X :" << X << ", Y :" << Y << std::endl;
            // std::cout << "etat :" << newEtat << ", flip :" << flip << std::endl;
        }
        else { // Pousse
            newEtat = tabState[Y+1][X+1][0];
            flip = tabState[Y+1][X+1][1];
            maxDelay = 7;
            // std::cout << "X :" << X << ", Y :" << Y << std::endl;
            // std::cout << "etat :" << newEtat << ", flip :" << flip << std::endl;
        }
    }
    if (newEtat != etat) {
        setEtat(newEtat);
    }


    //Calcul de la force que le MC veut rajouter
    Vector2D v(pushForceD - pushForceG, pushForceB - pushForceH);
    move(v);

    // On pousse
    addForce(v);
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


// Inplementer l'interface Controle pour pouvoir gérer les appels de Input
void Mc::zDown() {
    stockeur->getMc()->setPushForceH(1);
}
void Mc::zUp() {
    stockeur->getMc()->setPushForceH(0);
}
void Mc::sDown() {
    stockeur->getMc()->setPushForceB(1);
}
void Mc::sUp() {
    stockeur->getMc()->setPushForceB(0);
}
void Mc::qDown() {
    stockeur->getMc()->setPushForceG(1);
}
void Mc::qUp() {
    stockeur->getMc()->setPushForceG(0);
}
void Mc::dDown() {
    stockeur->getMc()->setPushForceD(1);
}
void Mc::dUp() {
    stockeur->getMc()->setPushForceD(0);
}
void Mc::spaceDown() {
    if( !(stockeur->getMc()->getDashOn())){
        stockeur->getMc()->getDepForce() *= dashValue;
        stockeur->getMc()->setStartDashTime(SDL_GetTicks());
        stockeur->getMc()->setDashOn(true);
    }
}

Attacks* Mc::getAttacks(){
    return attack;
}

int& Mc::getColor(){
    return color;
}



// Fonctions de sauvegarde de l'objet
std::string Mc::serialize(std::string& toWrite) {
	std::cout << "Serialisation" << std::endl;
	Entite::serialize(toWrite);
	// On n'enregistre que les paramètres nécessaires. Certains constructeur renseignent déjà les autres 
    // Ces paramètres nécessaires sont en fait les paramètres contextuels (susceptibles de changer à chaque instant)
	std::ostringstream oss;
    oss << dashValue << "|" << dashOn << "|" << color << "|";
	std::cout << "parsed" << std::endl;
	std::cout << "oss : " << oss.str() <<std::endl; 
    toWrite += oss.str();
    return "Mc";
}

void Mc::deSerialize(std::string& toRead) {
	Sprite::deSerialize(toRead);
    std::istringstream iss(toRead);
    std::string token;
    if (std::getline(iss, token, '|')) {
        dashValue = std::stof(token);
    }
    if (std::getline(iss, token, '|')) {
        dashOn = readBool(token);
    }
    if (std::getline(iss, token, '|')) {
        color = std::stoi(token);
    }
    std::cout << "fin deSerialize : ";
}