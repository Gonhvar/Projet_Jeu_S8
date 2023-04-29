#include "Entite.hpp"

Entite::Entite() : Sprite() {}
Entite::Entite(const Entite& other) {}
Entite::Entite(std::string& spriteName, uint8_t nbStates, std::vector<uint8_t>& nbFPE, Killable* parent) : Sprite(spriteName, nbStates, nbFPE) {
	possesseur = parent;
}


int Entite::getPV() {
	return PV;
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
	
	for (int i = 0; i < HITBOX_PTS; i++) {
		//On déplace les points qui compose le rectangle de la hitbox
		hitBox[i][0] += dx/FPS;
		hitBox[i][1] += dy/FPS;
	}
	
	//printf("hitbox1 : %f et %f\n", hitBox[0][0], hitBox[0][1]);
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