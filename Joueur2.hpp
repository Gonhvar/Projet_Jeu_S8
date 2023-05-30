#ifndef JOUEUR2_HPP
#define JOUEUR2_HPP

#pragma once
#include "Sprite.hpp"
#include "Bullets.hpp"

#define DECALAGE_J2 30

/*
const States etatsDeJoueur2 = {
	"noTexture",
	1,
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
*/

class Joueur2 : public Sprite {
protected:
	int mouseX;
	int mouseY;
	float k = 0.025;
	float frottement = 0.2;
	float vitesseActuelle[2] = {0, 0};

	std::vector<Bullets*> bullets;
	
public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	Joueur2();
	virtual ~Joueur2();
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void update();

	void deplacementDynamique();

	void newTir(int state, int directX, int directY);

	void removeBullet(Bullets* bullet);
};

#endif
