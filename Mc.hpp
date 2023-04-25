#ifndef MC_HPP
#define MC_HPP

#pragma once
#include "Entite.hpp"
#include <SDL2/SDL.h>

class Mc : public Entite {
protected :

public :
	Mc(Affichage& aff);

	void get_keypress();

	void doKeyDown(SDL_KeyboardEvent *event);
	void doKeyUp(SDL_KeyboardEvent *event);
};

#endif