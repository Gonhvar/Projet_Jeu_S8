#include "Entite.hpp"

std::vector<Entite*> Entite::allEntities;

Entite::Entite(const Entite& other) {}
Entite::Entite(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE], Killable* parent) : Sprite(sName, nbE, nbFPE) {
	possesseur = parent;
	std::cout << "passage ???" << std::endl;
	Entite::allEntities.push_back(this);
}


void Entite::autoSetHitBox() {
	hitBox[0][0] = _coord[0];
	hitBox[0][1] = _coord[1];
	hitBox[1][0] = _coord[0] + _largeur;
	hitBox[1][1] = _coord[1] + _hauteur;
}


int Entite::getPV() {
	return PV;
}

int Entite::getPVMax() {
	return PVMax;
}

void Entite::setPV(int health) {
	PV = health;
}

void Entite::changePV(int change) {
	PV += change;

	if(PV<=0){
		//Tuer l'Entite
	}
}

void Entite::translate(float dx, float dy) {
	_coord[0] += dx/FPS;
	_coord[1] += dy/FPS;
	
	for (uint8_t i = 0; i < HITBOX_PTS; i++) {
		//On déplace les points qui compose le rectangle de la hitbox
		hitBox[i][0] += dx/FPS;
		hitBox[i][1] += dy/FPS;
	}
	
	//printf("hitbox1 : %f et %f\n", hitBox[0][0], hitBox[0][1]);
}

void Entite::move(float moveX, float moveY) { // Fait se déplacer selon un vecteur à l'allure vitesse
	// C'est probablement là que je mettrai la détection de contacts.
	double norme = sqrt(moveX*moveX + moveY*moveY) + 0.000001;
    moveX /= norme;
    moveY /= norme;
	translate(moveX * vitesse,  moveY * vitesse);
}

bool Entite::contact(Entite* other) {
	if (hitBox[0][0] < other->hitBox[1][0] &&
		hitBox[1][0] > other->hitBox[0][0] &&
		hitBox[0][1] < other->hitBox[1][1] &&
		hitBox[1][1] > other->hitBox[0][1]) {
			std::cout << "contact" << std::endl;
			return true;
		}
	return false;
}


void Entite::mort() {
	std::cout << "Entite.mort() de " << this << std::endl;
}

float Entite::getDx(){
		return dx;
	}

float Entite::getDy(){
		return dy;
}