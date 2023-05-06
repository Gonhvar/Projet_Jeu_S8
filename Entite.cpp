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
		mort();
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
	//Distance entre les deux entite
	float distance = sqrt((other->_coord[0]-_coord[0])*(other->_coord[0]-_coord[0]) + (other->_coord[1]-_coord[1])*(other->_coord[1]-_coord[1]));
	float normeVPost;

	if (distance < v.norme + rayon + other->rayon) {
		normeVPost = distance - rayon - other->rayon;
		if (v.norme) {
			v.normeToV(normeVPost);
		} 
		else {
			v.redef(other->_coord[0] - _coord[0], other->_coord[1] - _coord[1]);
			// Pas fini :((((
			// ^^^ Yes, ça serait bien que le joueur soit repoussé ici 
			//(et peut etre le mob mais certains seront à distance donc étrange)

			// Le mob est repoussé en dehors. Le problème est qu'il y a un problème
			// dans le calcul si l'Entite se déplace d'un vecteur nul.
		}
	}
	
	return v;
}

Vector2D& Entite::moveCollisionRectangle(Entite* other, Vector2D& v) {
	// Ce code est moche mais je voulais d'abord vérifier qu'il marche avant de l'optimiser
	// Ptn ce que c'est moche X(
	bool contact[4];
	contact[0] = hitBox[0][0] < other->hitBox[1][0]; // On est à gauche
	contact[1] = hitBox[1][0] > other->hitBox[0][0]; // On est à droite
	contact[2] = hitBox[0][1] < other->hitBox[1][1]; // On est au-dessus
	contact[3] = hitBox[1][1] > other->hitBox[0][1]; // On est en-dessous
	uint8_t nbContact = contact[0] + contact[1] + contact[2] + contact[3];
	if (nbContact == 3) { // Empêche de rentrer dans other
		if (!contact[0]) { // On est à droite
			v.x = std::max(v.x, other->hitBox[1][0] - hitBox[0][0]);
		}
		else if (!contact[1]) { // On est à gauche
			v.x = std::min(v.x, other->hitBox[0][0] - hitBox[1][0]);
		}
		else if (!contact[2]) { // On est en-dessous
			v.y = std::max(v.y, other->hitBox[1][1] - hitBox[0][1]);
		}
		else if (!contact[3]) { // On est au-dessus
			v.y = std::min(v.y, other->hitBox[0][1] - hitBox[1][1]);
		}
	} else if (nbContact == 4) { // Repousse this en dehors de other
		uint8_t indiceMin = 0;
		float min = other->hitBox[1][0] - hitBox[0][0], min1;

		min1 = hitBox[1][0] - other->hitBox[0][0];
		if (min1 < min) {
			min = min1;
			indiceMin = 1;
		}
		min1 = other->hitBox[1][1] - hitBox[0][1];
		if (min1 < min) {
			min = min1;
			indiceMin = 2;
		}
		min1 = hitBox[1][1] - other->hitBox[0][1];
		if (min1 < min) {
			min = min1;
			indiceMin = 3;
		}

		switch (indiceMin) {
			case 0 :
				v.x = other->hitBox[1][0] - hitBox[0][0];
				break;
			case 1 :
				v.x = other->hitBox[0][0] - hitBox[1][0];
				break;
			case 2 :
				v.y = other->hitBox[1][1] - hitBox[0][1];
				break;
			case 3 :
				v.y = other->hitBox[0][1] - hitBox[1][1];
				break;
		}
		v.redef(v.x, v.y);
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