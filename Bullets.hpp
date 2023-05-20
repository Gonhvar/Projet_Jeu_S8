#ifndef BULLETS_HPP
#define BULLETS_HPP

#pragma once
#define BASICBULLETSPEED 200.0
#include "Entite.hpp"

/*
const States etatsDeBullets = {
	"noTexture",
	1,
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
*/

class Bullets : public Entite{
protected:
	
public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	Bullets();
	Bullets(int state, float x, float y);
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void update();
};

#endif
