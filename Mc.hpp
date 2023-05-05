#ifndef MC_HPP
#define MC_HPP

#pragma once
#include "Killable.hpp"
#include "Attacks.hpp"

class Attacks;

const States etatsDesMc = { // Eviter de le modifier
	"Robot",
	1,
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};


class Mc : public Killable {
protected :
	//Multiplicateur de vitesse
	float dashValue = 0;
	bool dashOn = false;
	uint32_t startDashTime;
	uint32_t actualDashTime;
	Attacks* attack;

public :
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	Mc();
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void update();

	void get_keypress();

	void doKeyDown(SDL_KeyboardEvent *event);
	void doKeyUp(SDL_KeyboardEvent *event);
};

#endif