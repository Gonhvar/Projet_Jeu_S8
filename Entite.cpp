#include "Entite.hpp"

Entite::Entite(const Entite& other) {}
Entite::Entite(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE], Killable* parent) : Sprite(sName, nbE, nbFPE) {
	possesseur = parent;
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
	//std::cout << "move X :" << moveX << " move Y :" << moveY << std::endl;
	translate(moveX * vitesse,  moveY * vitesse);
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