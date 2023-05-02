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

void Entite::autoSetHitBox() {
	// Pour l'instant on suppose que l'angle est nul (c'est faux mais j'ai la flemme de faire le calcul)
	hitBox[0][0] = _coord[0];
	hitBox[3][0] = _coord[0];
	hitBox[1][0] = _coord[0] + _largeur;
	hitBox[2][0] = _coord[0] + _largeur;

	hitBox[0][1] = _coord[1];
	hitBox[1][1] = _coord[1];
	hitBox[2][1] = _coord[1] + _hauteur;
	hitBox[3][1] = _coord[1] + _hauteur;

	rayon = sqrt(_largeur*_largeur + _hauteur*_hauteur) /2;
}


void Entite::translate(float depX, float depY) {
	_coord[0] += depX/FPS;
	_coord[1] += depY/FPS;
	
	// std::cout << "hitbox :" << std::endl;
	// std::cout << "coord : " << _coord[0] << ", " << _coord[1] << std::endl; 
	for (uint8_t i = 0; i < HITBOX_PTS; i++) {
		//On déplace les points qui compose le rectangle de la hitbox
		// std::cout << "i " << hitBox[i][0] << ", " << hitBox[i][1] << std::endl; 
		hitBox[i][0] += depX/FPS;
		hitBox[i][1] += depY/FPS;
		// std::cout << "f " << hitBox[i][0] << ", " << hitBox[i][1] << std::endl;
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

float* Entite::collision(float* d) {
	std::vector<Entite*> otherEntites;
	float distance;
	float norme = sqrt(d[0]*d[0] + d[1]*d[1]);
	for (Entite* e : otherEntites) {
		distance = sqrt((e->_coord[0] - _coord[0]) * (e->_coord[0] - _coord[0]) + (e->_coord[1] - _coord[1])*(e->_coord[1] - _coord[1]));
		if (e->possesseur != possesseur &&  // Un Killable peut se rentrer dedans 
			distance < rayon + e->rayon + norme + 0.5) // on vérifie qu'il est à porté (diminue le temps de calcul si la zone est peu densement peuplée)
		{
			for (uint8_t shb=0; shb < HITBOX_PTS; shb++) {
				for (uint8_t ohb=0; ohb < HITBOX_PTS; ohb++) {

				}
			}
		}
	}
}

void Entite::rotate(float alpha) {
	// alpha en radians
	_coord[2] += alpha;
	while (_coord[2] > M_PI) _coord[2] -= 2*M_PI;
	while (_coord[2] <= -M_PI) _coord[2] += 2*M_PI;
	float OA[2];
	_coord[0] += _largeur/2; // ACCELERE LE CALCUL MAIS CE N'EST PAS PROPRE !!!
	_coord[1] += _hauteur/2; // IL NE FAUT PAS INTEROMPRE CETTE FONCTION
	for (uint8_t i = 0; i < HITBOX_PTS; i++) {
		OA[0] = hitBox[i][0] - _coord[0];
		OA[1] = hitBox[i][1] - _coord[1];

		hitBox[i][0] = OA[0] * cos(alpha) - OA[1] * sin(alpha) + _coord[0];
		hitBox[i][1] = OA[1] * cos(alpha) + OA[0] * sin(alpha) + _coord[1];
	}
	_coord[0] -= _largeur/2;
	_coord[1] -= _hauteur/2;
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