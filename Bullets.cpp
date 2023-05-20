#include "Bullets.hpp"


Bullets::Bullets(){

}

Bullets::Bullets(int state, float directX, float directY) {
	//Mettre l'hitbox
	dx = directX;
	dy = directY;
	depForce = BASICBULLETSPEED;
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

	_coord[0] = joueur2->getX();
	_coord[1] = joueur2->getY();

	autoSetHitBox();
	addSprite();
	std::cout << "YEAHHHHH" << std::endl;
}

void Bullets::update(){
	Vector2D v(dx, dy);
	move(v);
	translate(v);
	//test si touche quoique ce soit (meme bords de la map)
}
