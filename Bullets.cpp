#include "Bullets.hpp"
#include "Joueur2.hpp"

/* CONSTRUCTEURS ET DESTRUCTEURS */
Bullets::Bullets(int state, float directX, float directY, Joueur2* papa, short fact) {
	//Mettre l'hitbox
    faction = 0;
	speed.redef(directX, directY);
	speed.normeToV(BASICBULLETSPEED);
	parent = papa;
	masse = 1;
	frottements = 0;
	_hauteur = 16;
	_largeur = 16;

	onScreen = true;
	//states = &(etatsDeBullets);
		States* newStates = new States(); // newStates est un pointeur temporaire
		newStates->spriteName = "Bullets"; // Il n'est pas const donc on peut modifier ce qu'il y a à l'adresse
		newStates->nbEtats = 1;
		newStates->nbFrameParEtat[0] = 1;
		for (int i=1; i<newStates->nbEtats; i++) {
			newStates->nbFrameParEtat[i] = 0;
		}
		states = newStates;

	_coord[0] = stockeur->getJ2()->getX();
	_coord[1] = stockeur->getJ2()->getY();

	stateRect.w = 32;
    stateRect.h = 32;

	autoSetHitBox();
	hitBoxType(1, 0);
	addSprite();
	//std::cout << "YEAHHHHH" << std::endl;
}

Bullets::~Bullets() {
    std::cout << "Delete Bullets" << std::endl;
	parent->removeBullet(this);
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

void Bullets::update(){
    if (Sprite::stockeur->printEverything) std::cout << "Bullets::update() : " << this << std::endl;
	Vector2D v(dx, dy);
	move(v);
	addForce(v);
	//test si touche quoique ce soit (meme bords de la map)
}

void Bullets::reactionContact(Entite* other) {
	if (Sprite::stockeur->printEverything) {
		std::cout << "Contact Bullets : " << this << "(" << states->spriteName << ")" << " ->" << other << std::endl;
	}
	if (faction != other->getFaction()) {
		other->changePV(10);
	}
	markedForDeath = true;
}