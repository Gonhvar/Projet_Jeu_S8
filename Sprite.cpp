#include "Sprite.hpp"
#include "affichage.hpp"

Affichage* Sprite::afficheur;

Map* Sprite::map;
Stockeur* Sprite::stockeur;

int Sprite::mode = MODE_JEU; // variable globale définissant l'état du jeu;


/* CONSTRUCTEURS ET DESTRUCTEURS */
Sprite::Sprite() {
	Sprite::stockeur->addSprites(this);
}


Sprite::Sprite(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE]) {
	std::cout << "création d'un Sprite" << std::endl;
	Sprite::stockeur->addSprites(this);

	States* newStates = new States(); // newStates est un pointeur temporaire
	newStates->spriteName = sName; // Il n'est pas const donc on peut modifier ce qu'il y a à l'adresse
	newStates->nbEtats = nbE;
	for (int i=0; i<nbE; i++) {
		newStates->nbFrameParEtat[i] = nbFPE[i];
	}
	states = newStates;
	addSprite("Sprite");
	

	std::cout << "Sprite texture : " << texture << std::endl;
}

Sprite::~Sprite() {
    std::cout << "Delete Sprite" << std::endl;
	Sprite::stockeur->removeSprites(this);
}

/* FIN CONSTRUCTEURS ET DESTRUCTEURS */


float* Sprite::getCoord() {
	return _coord;
}
float Sprite::getX() {
	return _coord[0];
}
float Sprite::getY() {
	return _coord[1];
}

float Sprite::getSpriteX() {
	return _coord[0] - _largeur/2;
}

float Sprite::getSpriteY() {
	return _coord[1] - _hauteur/2;
}

void Sprite::setCoord(float x, float y, float theta) {
	_coord[0] = x;
	_coord[1] = y;
	_coord[2] = theta;
}
void Sprite::setCoord(float* coordonnees) {
	_coord[0] = coordonnees[0];
	_coord[1] = coordonnees[1];
	_coord[2] = coordonnees[2];
}

float& Sprite::getLargeur() {
	return _largeur;
}
void Sprite::setLargeur(float L) {
	_largeur = L;
}

float& Sprite::getHauteur() {
	return _hauteur;
}
void Sprite::setHauteur(float H) {
	_hauteur = H;
}


bool Sprite::getOnScreen(){
	return onScreen;
};
void Sprite::setOnScreen(bool toBe){
	onScreen = toBe;
}

void Sprite::addSprite(std::string className){
	afficheur->visit(this, className, states->spriteName);
}

SDL_Texture* Sprite::getTexture() {
	return texture;
}

void Sprite::setTexture(SDL_Texture* t) {
	texture = t;
}

const SDL_Rect* Sprite::getRightRectangle() {
	return &stateRect;
}

const States* Sprite::getStates() {
	return states;
}

void Sprite::setEtat(uint8_t toBe) {
	if (toBe < states->nbEtats) {
		etat = toBe;
		frame = 0;
		delay = maxDelay;
		stateRect.y = stateRectIn.h * etat + stateRectIn.y;
	} else if (Sprite::stockeur->printEverything) {
		std::cout << "Dans Sprite::setEtat : on demande à passer dans l'état " << (int)toBe << ",  mais il n'y en a que " << (int) states->nbEtats << std::endl;
	}
}

void Sprite::update() {
	if (!delay) {
		frame = (frame+1)%states->nbFrameParEtat[etat];
		delay = maxDelay;
		stateRect.x = stateRectIn.w * frame + stateRectIn.x;
	}
	else delay--;
}

bool Sprite::getFlip() {
	return flip;
}

const std::string Sprite::getName(){
	return states->spriteName;
}


// Fonctions de sauvegarde de l'objet

std::string Sprite::serialize(std::string& toWrite) {
	std::cout << "Serialisation" << std::endl;
	// On n'enregistre que les paramètres nécessaires. Certains constructeur renseignent déjà les autres 
    // Ces paramètres nécessaires sont en fait les paramètres contextuels (susceptibles de changer à chaque instant)
	std::ostringstream oss;
    oss << _coord[0] << "|" << _coord[1] << "|" << _coord[2] << "|" << 
	onScreen << "|" << _largeur << "|" << _hauteur << "|" <<
	(int)maxDelay << "|" << (int)delay << "|" << etat << "|" << frame << "|" << flip << "|";
	std::cout << "parsed" << std::endl;
	std::cout << "oss : " << oss.str() <<std::endl; 
    toWrite += oss.str();
    return "Sprite";
}

std::istringstream& Sprite::deSerialize(std::istringstream& iss) {
    // std::istringstream iss(toRead);
    std::string token;
    if (std::getline(iss, token, '|')) {
        _coord[0] = std::stof(token);
    }
    if (std::getline(iss, token, '|')) {
        _coord[1] = std::stof(token);
    }
    if (std::getline(iss, token, '|')) {
        _coord[2] = std::stof(token);
    }
    if (std::getline(iss, token, '|')) {
        onScreen = readBool(token);
    }
    if (std::getline(iss, token, '|')) {
        _largeur = std::stof(token);
    }
    if (std::getline(iss, token, '|')) {
        _hauteur = std::stof(token);
    }
    if (std::getline(iss, token, '|')) {
        maxDelay = std::stoi(token);
    }
    if (std::getline(iss, token, '|')) {
        delay = std::stoi(token);
    }
    if (std::getline(iss, token, '|')) {
        etat = std::stoi(token);
    }
    if (std::getline(iss, token, '|')) {
        frame = std::stoi(token);
    }
    if (std::getline(iss, token, '|')) {
        flip = readBool(token);
    }
    
    std::cout << "fin deSerialize Sprite" << std::endl;
	return iss;
}

bool Sprite::readBool(std::string& toRead) {
	return toRead == "1";
}