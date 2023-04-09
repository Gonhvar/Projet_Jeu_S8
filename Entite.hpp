#ifndef ENTITE_HPP
#define ENTITE_HPP

#pragma once
#include "Sprite.hpp"

#define HITBOX_PTS 2

class Entite : public Sprite {
protected :
	int PV = 1;
	float hitBox[HITBOX_PTS][2] = {
		{0,0},
		{0,0}
	};
	short int orientation = 1; // Prend -1 ou 1 : <- ou ->

public :
	/* CONSTRUCTEURS ET DESTRUCTEURS */
	Entite();
	Entite(const Entite& other);
	Entite(std::string& spriteName, Affichage& aff);
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	int getPV();
	void setPV(int health);
	void changePV(int change);

	void translate(float dx, float dy);

	virtual void mort();
};

#endif