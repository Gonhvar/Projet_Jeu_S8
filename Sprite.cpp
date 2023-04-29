#include "Sprite.hpp"
#include "affichage.hpp"


Affichage* Sprite::afficheur;
Sprite* Sprite::joueur;

/* CONSTRUCTEURS ET DESTRUCTEURS */
Sprite::Sprite(const Sprite& other) {
	*this = other;
}



Sprite::Sprite(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE]) {
	States* newStates = new States(); // newStates est un pointeur temporaire
	newStates->spriteName = sName; // Il n'est pas const donc on peut modifier ce qu'il y a à l'adresse
	newStates->nbEtats = nbE;
	for (int i=0; i<nbE; i++) {
		newStates->nbFrameParEtat[i] = nbFPE[i];
	}
	states = newStates;
	addSprite();
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

void Sprite::addSprite(){
	afficheur->visit(this, states);
}

TexturePack* Sprite::getTexture() {
	return texture;
}

void Sprite::setTexture(TexturePack* t) {
	if (texture != nullptr) {
		std::cout << "gros risque de fuite de mémoire à Sprite::setTexture" << std::endl;
		// Techniquement ce n'est peut-être pas une fuite de mémoire étant donné que ce n'est pas le Sprite qui stocke directement ses textures
	}
	texture = t;
}

SDL_Texture* Sprite::getRightTexture() {
	// std::cout << "in Sprite::getRightTexture, etat=" << etat << "  frame=" << frame << std::endl;
	// std::cout << "texture : " << texture << std::endl;
	// std::cout << "texture[" << (*texture).size() << "][" << (*texture)[0].size() << "]" << std::endl;
	return (*texture)[etat][frame];
}

const States* Sprite::getStates() {
	return states;
}

void Sprite::setEtat(uint8_t toBe) {
	if (toBe >= states->nbEtats) {
		std::cout << "Dans Sprite::setEtat : on demande à passer dans l'état " << (int)toBe << ",  mais il n'y en a que " << (int) states->nbEtats << std::endl;
	} else {
		etat = toBe;
	}
}

void Sprite::update() {
	if (!delay) {
		frame = (frame+1)%states->nbFrameParEtat[etat];
		delay = maxDelay;
	}
	else delay--;
}