#include "Entite.hpp"

Entite::Entite() {};
Entite::Entite(const Entite& other) {

};

int Entite::getPV() {
	return PV;
}

void Entite::setPV(int health) {
	PV = health;
}

void Entite::damage(int damage) {
	PV -= damage;
}