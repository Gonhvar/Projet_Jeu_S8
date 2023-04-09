
#include "Entite.hpp"

Entite::Entite() {}
Entite::Entite(const Entite& other) {}
Entite::Entite(std::string& spriteName, Affichage& aff) : Sprite(spriteName, aff) {}

int Entite::getPV() {
	return PV;
}

void Entite::setPV(int health) {
	PV = health;
}

void Entite::changePV(int change) {
	PV += change;

	if(PV<=0){
		//Tuer l'entitee
	}
}

void Entite::translate(float dx, float dy) {
	_coord[0] += dx;
	_coord[1] += dy;

	for (int i = 0; i < HITBOX_PTS; i++) {
		hitBox[i][0] += dx;
		hitBox[i][1] += dy;
	}
}

void Entite::mort() {
	std::cout << "Entite.mort() de " << this << std::endl;
}