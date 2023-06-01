#include "Bullets.hpp"

/* CONSTRUCTEURS ET DESTRUCTEURS */

Bullets::Bullets(int state, float directX, float directY, Entite* papa, short fact) {
	//Mettre l'hitbox
    faction = fact;
	speed.redef(directX, directY);
	speed.normeToV(BASICBULLETSPEED);
	parent = papa;
	_hauteur = 16;
	_largeur = 16;

	onScreen = true;
	//states = &(etatsDeBullets);
		States* newStates = new States(); // newStates est un pointeur temporaire
		newStates->spriteName = "Glow_Bullet"; // Il n'est pas const donc on peut modifier ce qu'il y a à l'adresse
		newStates->nbEtats = 1;
		newStates->nbFrameParEtat[0] = 1;
		for (int i=1; i<newStates->nbEtats; i++) {
			newStates->nbFrameParEtat[i] = 0;
		}
		states = newStates;

	_coord[0] = papa->getX();
	_coord[1] = papa->getY();

	stateRectIn.w = 256;
    stateRectIn.h = 128;
    stateRectIn.x = 0;
    stateRectIn.y = 0;
    stateRect.w = 256;
    stateRect.h = 128;

	masse = 1;
	frottements = 0;
	rayon = 8;	
	autoSetHitBox();
	hitBoxType(1, 0);
	addSprite("Bullets");
}

Bullets::~Bullets() {
    std::cout << "Delete Bullets" << std::endl;
	stockeur->removeBullet(this);
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
	other->changePV(10);
	markedForDeath = true;
}
