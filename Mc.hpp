#ifndef MC_HPP
#define MC_HPP

#pragma once
#include "Killable.hpp"
//#include <SDL2/SDL.h>

const States etatsDesMc = { // Eviter de le modifier
	"Robot",
	1,
	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

class Mc : public Killable {
protected :
	
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