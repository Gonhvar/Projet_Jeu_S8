#include "Entite.hpp"

std::vector<Entite*> Entite::allEntities;

Entite::Entite(const Entite& other) {}
Entite::Entite(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE], Killable* parent) : Sprite(sName, nbE, nbFPE) {
	possesseur = parent;
	//Entite::allEntities.push_back(this);
}


void Entite::autoSetHitBox() {
	hitBox[0][0] = _coord[0] - _largeur/2;
	hitBox[0][1] = _coord[1] - _hauteur/2;
	hitBox[1][0] = _coord[0] + _largeur/2;
	hitBox[1][1] = _coord[1] + _hauteur/2;
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

void Entite::translate(Vector2D& v) {
	// Décale l'Entite de dx, dy en faisant fi de toute considération
	_coord[0] += v.x;
	_coord[1] += v.y;
	
	for (uint8_t i = 0; i < HITBOX_PTS; i++) {
		//On déplace les points qui composent le rectangle de la hitbox
		hitBox[i][0] += v.x;
		hitBox[i][1] += v.y;
	}
	
	//printf("hitbox1 : %f et %f\n", hitBox[0][0], hitBox[0][1]);
}

Vector2D& Entite::move(Vector2D& v) {
	// Normalise le vecteur à la vitesse this->vitesse
	v.normeToV(vitesse/FPS);
	return v;
}

Vector2D& Entite::moveCollisionCercle(Entite* other, Vector2D& v) {
	// On lui passe l'Entite avec laquelle on prévérifie la collision puis on modifie en conséquence le déplacement voulu
	float distance = sqrt((other->_coord[0]-_coord[0])*(other->_coord[0]-_coord[0]) + (other->_coord[1]-_coord[1])*(other->_coord[1]-_coord[1]));
	float normeVPost;
	if (distance < v.norme + rayon + other->rayon) {
		normeVPost = distance - rayon - other->rayon;
		if (v.norme) {
			v.normeToV(normeVPost);
		} else {
			v.redef(other->_coord[0] - _coord[0], other->_coord[1] - _coord[1]);
			// Pas fini :((((
		}
	}
	
	return v;
}

bool Entite::contact(Entite* other) {
	if (hitBox[0][0] < other->hitBox[1][0] &&
		hitBox[1][0] > other->hitBox[0][0] &&
		hitBox[0][1] < other->hitBox[1][1] &&
		hitBox[1][1] > other->hitBox[0][1]) {
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