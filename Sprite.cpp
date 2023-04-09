#include "Sprite.hpp"

/* CONSTRUCTEURS ET DESTRUCTEURS */
Sprite::Sprite() {};

Sprite::Sprite(const Sprite& other) {
	// Copie profonde
	*this = other;
	texture = new SDL_Texture(); // J'essaie de faire une copie de la texture (j'espère qu'il n'y a pas de pointeur dans other.texture
	*texture = *(other.texutre);
};

Sprite::Sprite(char* textureFileName) {
	loadTexture(textureFileName);
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */


float* Sprite::getCoord() {
	return _coord;
}

void Sprite::setCoord(float& x, float& y, float& theta) {
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



SDL_Texture* Sprite::loadTexture(char* filename)
{
	if (texture != nullptr) {
		delete texture;
	}
	texture = IMG_LoadTexture(app.renderer, filename);
	return nullptr_t;
}

SDL_Texture* getTexture(){
	return texture;
}