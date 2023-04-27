#ifndef ENTITE_HPP
#define ENTITE_HPP

#pragma once
#include "Sprite.hpp"

#define HITBOX_PTS 2
#define FPS 60

class Entite : public Sprite {
protected :
	float hitBox[HITBOX_PTS][2] = {
		{0,0},
		{0,0}
	};
	short int orientation = 1; // Prend -1 ou 1 : <- ou ->
	float vitesse = 1;
	float dx = 0;
    float dy = 0;



public :
	/* CONSTRUCTEURS ET DESTRUCTEURS */
	Entite();
	Entite(const Entite& other);
	//Entite(std::string& spriteName, Affichage& aff);
	Entite(std::string& spriteName);
	Entite(std::string& spriteName, uint8_t etats, std::vector<uint8_t>& frames);
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void translate(float dx, float dy);

	float getDx();
	float getDy();

};

#endif