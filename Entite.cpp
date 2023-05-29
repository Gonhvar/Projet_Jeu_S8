#include "Entite.hpp"

/* CONSTRUCTEURS ET DESTRUCTEURS */
Entite::Entite() {
	speed.redef(0,0);
}

Entite::Entite(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE]) : Sprite(sName, nbE, nbFPE) {
	speed.redef(0,0);
}

Entite::~Entite(){
    std::cout << "Delete Entite" << std::endl;
	if (isCirc) {
		Sprite::stockeur->removeCircEntite(this);
	}
	if (isRect) {
		Sprite::stockeur->removeRectEntite(this);
	}
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

void Entite::autoSetHitBox() {
	hitBox[0][0] = _coord[0] - _largeur/2;
	hitBox[0][1] = _coord[1] - _hauteur/2;
	hitBox[1][0] = _coord[0] + _largeur/2;
	hitBox[1][1] = _coord[1] + _hauteur/2;
}

void Entite::hitBoxType(bool circ, bool rect) {
	// Met dans les listes mais n'enlève pas
	if (circ) {
		Sprite::stockeur->addCircEntite(this);
		isCirc = true;
	}
	if (rect) {
		Sprite::stockeur->addRectEntite(this);
		isRect = true;
	}
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
	PV -= change;
	//std::cout << "PV :" << PV << " Change :" << change << std::endl; 
	if(PV<=0){
		//Tuer l'Entite
		mort();
	}
}

void Entite::translate(Vector2D& v) {
	// Décale l'Entite de v en faisant fi de toute considération
	_coord[0] += v.x;
	_coord[1] += v.y;
	
	for (uint8_t i = 0; i < HITBOX_PTS; i++) {
		//On déplace les points qui composent le rectangle de la hitbox
		hitBox[i][0] += v.x;
		hitBox[i][1] += v.y;
	}
}

void Entite::autoTranslate() {
	// Décale l'Entite de v en faisant fi de toute considération
	_coord[0] += speed.x;
	_coord[1] += speed.y;
	
	for (uint8_t i = 0; i < HITBOX_PTS; i++) {
		//On déplace les points qui composent le rectangle de la hitbox
		hitBox[i][0] += speed.x;
		hitBox[i][1] += speed.y;
	}
}

Vector2D& Entite::move(Vector2D& v) {
	// Normalise le vecteur à this->depForce
	v.normeToV(depForce);
	return v;
}

Vector2D& Entite::moveCollisionCercle(Entite* other, Vector2D& v) {
	// On lui passe l'Entite avec laquelle on prévérifie la collision puis on modifie en conséquence le déplacement voulu
	
	//Distance entre les deux entite
	float distance = sqrt((other->_coord[0]-_coord[0])*(other->_coord[0]-_coord[0]) + (other->_coord[1]-_coord[1])*(other->_coord[1]-_coord[1]));
	float normeVPost;

	if (distance < v.norme + rayon + other->rayon) {
		normeVPost = distance - rayon - other->rayon;
		v.redef(other->_coord[0] - _coord[0], other->_coord[1] - _coord[1]);
		v.normeToV(normeVPost);
	}
	
	return v;
}

void Entite::moveCollisionCercle2(Entite* other, Vector2D& v) {

	float distX = other->_coord[0] - _coord[0];
	float distY = other->_coord[1] - _coord[1];

	float A = v.norme * v.norme;
	float B = -2* (v.x*(distX) + v.y*(distY));
	float C = distX*distX + distY*distY - (rayon + other->rayon)*(rayon + other->rayon);

	// SI C EST NUL ON A UNE INTERSECTION ALPHA = 0 : CA VEUT DIRE QUE LES DEUX ENTITE SONT EN CONTACT


	float delta = B*B - 4*A*C;
	if (delta > 0) { // Il y aura intersection 
					// (s'il n'y en a qu'une alors on frolle et ça n'aura pas d'impact donc on ignore ce cas) 
		float alpha1 = (-B + sqrt(delta))/(2*A);
		float alpha2 = (-B - sqrt(delta))/(2*A);

		if (alpha1 > alpha2) { // On tri alpha1 et alpha2 pour raccourcir les tests suivants
			float temp = alpha1;
			alpha1 = alpha2;
			alpha2 = temp;
		}

		if (alpha1 < 0) {
			if (alpha2 > 0) { // On est dans l'Entite
				Vector2D v2(_coord[0] - other->_coord[0], _coord[1] - other->_coord[1]);
				v2.normeToV(rayon + other->rayon - v2.norme + 0.0001);
				Vector2D v3(v2.x, v2.y);
				v2 *= (other->masse / (masse + other->masse));
				v3 *= -(masse / (masse + other->masse));
				
				v += v2;
				other->speed += v3;

				reactionContact(other);
			}
		}
		else if (alpha1 < 1){ // on va cogner l'Entite
			alpha1 -= 0.0001;
			alpha1 = alpha1 < 0.0001 ? 0 : alpha1;

			Vector2D v2(_coord[0] + v.x*alpha1 - other->_coord[0], 
						_coord[1] + v.y*alpha1 - other->_coord[1]);
			v2.normeToV(1);
			v2 *= (v.x - other->speed.x)*v2.x + (v.y- other->speed.y)*v2.y; // On multiplie par le produit scalaire avec la vitesse relative
										// i.e à quel point on frappe other

			// this est repoussé selon la normale à l'intersection proportionnelement à la masse de l'autre
			// v.x -= v2.x * (other->masse / (masse + other->masse));
			// v.y -= v2.y * (other->masse / (masse + other->masse));
			v.plus(
				-v2.x * (other->masse / (masse + other->masse)),
				-v2.y * (other->masse / (masse + other->masse))
			);

			// pareil pour l'autre
			v2.x = v2.x * (masse / (masse + other->masse));
			v2.y = v2.y * (masse / (masse + other->masse));
			other->speed += v2;

			reactionContact(other);
		}
	}

}

Vector2D& Entite::moveCollisionRectangle(Entite* other, Vector2D& v) {
	// Ce code est moche mais je voulais d'abord vérifier qu'il marche avant de l'optimiser

	// Apparamment, il n'y a pas vraiment mieux en terme d'optimisation
	
	bool contact[4];
	contact[0] = hitBox[0][0] < other->hitBox[1][0]; // On est à gauche
	contact[1] = hitBox[1][0] > other->hitBox[0][0]; // On est à droite
	contact[2] = hitBox[0][1] < other->hitBox[1][1]; // On est au-dessus
	contact[3] = hitBox[1][1] > other->hitBox[0][1]; // On est en-dessous
	uint8_t nbContact = contact[0] + contact[1] + contact[2] + contact[3];
	if (nbContact == 3) { // Empêche this de rentrer dans other
		if (!contact[0]) { // On est à droite
			v.x = std::max(v.x, other->hitBox[1][0] - hitBox[0][0]);
		}
		else if (!contact[1]) { // On est à gauche
			v.x = std::min(v.x, other->hitBox[0][0] - hitBox[1][0]);
		}
		else if (!contact[2]) { // On est en-dessous
			v.y = std::max(v.y, other->hitBox[1][1] - hitBox[0][1]);
		}
		else { // On est au-dessus
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
				v.x += other->hitBox[1][0] - hitBox[0][0];
				break;
			case 1 :
				v.x += other->hitBox[0][0] - hitBox[1][0];
				break;
			case 2 :
				v.y += other->hitBox[1][1] - hitBox[0][1];
				break;
			case 3 :
				v.y += other->hitBox[0][1] - hitBox[1][1];
				break;
		}
		v.redef(v.x, v.y);
	}
	return v;
}


void Entite::updateSpeedWithCollisions() {
	// Pour toutes les autres Entite, appel moveCollisionCercle2 et moveCollisionRectangle
	// et met à jour la vitesse de l'Entite en prenant en compte ses frottements
	if (Sprite::stockeur->printEverything) {
		std::cout << "Entite::update() (" << states->spriteName << ")" << std::endl;
		if (states->spriteName == "Bord2") {
			printSelf();
		}
	}

	addForce(-speed.x*frottements, -speed.y*frottements);

	// Collision avec les cercles :
	if (isCirc) { // Permet d'éviter la vérification du contact de l'Entite avec elle-même
		std::vector<Entite*>& list1 = *(stockeur->getCircEntiteVector());
		for (Entite* entite : list1) { // max 65000 Entite :O
			if (this != entite) {
				// On pourrait ajouter un test pour vérifier que l'Entite est à porté.
				Entite::moveCollisionCercle2(entite, speed);
			}
    	}
	}
	else {
		std::vector<Entite*>& list1 = *(stockeur->getCircEntiteVector());
		for (Entite* entite : list1) { // max 65000 Entite :O
			// On pourrait ajouter un test pour vérifier que l'Entite est à porté.
			Entite::moveCollisionCercle2(entite, speed);
		}
	}


    // Collision avec les rectangles :
	if (isRect) {
		std::vector<Entite*>& list2 = *(stockeur->getRectEntiteVector());
		for (Entite* entite : list2) { // max 65000 Entite :O
			if (this != entite) {
				// On pourrait ajouter un test pour vérifier que l'Entite est à porté.
				Entite::moveCollisionRectangle(entite, speed);
			}
		}
	}
	else {
		std::vector<Entite*>& list2 = *(stockeur->getRectEntiteVector());
		for (Entite* entite : list2) { // max 65000 Entite :O
			// On pourrait ajouter un test pour vérifier que l'Entite est à porté.
			Entite::moveCollisionRectangle(entite, speed);
		}
	}
}

bool Entite::contact(Entite* other) {
	// Renvoie true si this et other ont une intersection de hitBox non nulle
	return (hitBox[0][0] < other->hitBox[1][0] &&
		hitBox[1][0] > other->hitBox[0][0] &&
		hitBox[0][1] < other->hitBox[1][1] &&
		hitBox[1][1] > other->hitBox[0][1]);
}

void Entite::reactionContact(Entite* other) {
	// Fonction appellée quand this entre en contact avec other
	if (Sprite::stockeur->printEverything) {
		std::cout << "Contact Entite : " << this << "(" << states->spriteName << ")" << " ->" << other << "(" << other->states->spriteName << ")"<< std::endl;
	}
}

void Entite::mort() {
	std::cout << "Entite.mort() de " << this << std::endl;
	markedForDeath = true;
}

float Entite::getDx(){
		return dx;
	}

float Entite::getDy(){
		return dy;
}

int Entite::getAttackDmg(){
    return attackDamage;
}

void Entite::addForce(float fx, float fy) {
	// Ajoute l'intégrale de l'accélération avec durant cette frame à speed
	speed.plus(
		fx/(masse*FPS),
		fy/(masse*FPS)
	);
}

void Entite::addForce(Vector2D& v) {
	// Ajoute l'intégrale de l'accélération avec durant cette frame à speed
	speed.plus(
		v.x/(masse*FPS),
		v.y/(masse*FPS)
	);
}

float& Entite::getDepForce(){
	return depForce;
}

void Entite::printSelf() {
	std::cout << "name :" << std::endl;
	std::cout << "\t PV = " << PV << std::endl;
	std::cout << "\t PVMax = " << PVMax << std::endl;
	std::cout << "\t attackDamage = " << attackDamage << std::endl;
	std::cout << "\t hitBox : " << "[" << hitBox[0][0] << ", " << hitBox[0][1] << "], [" << hitBox[1][0] << ", " << hitBox[1][1] << "]" << std::endl;
	std::cout << "\t rayon = " << rayon << std::endl;
	std::cout << "\t depForce = " << depForce << std::endl;
	std::cout << "\t masse = " << masse << std::endl;
	std::cout << "\t frottements = " << frottements << std::endl;
	std::cout << "\t speed = "; speed.printSelf();
	std::cout << "\t isCirc = " << isCirc << std::endl;
	std::cout << "\t isRect = " << isRect << std::endl;
	std::cout << "\t faction = " << faction << std::endl;
}