#ifndef BULLETS_HPP
#define BULLETS_HPP

#pragma once
#define BASICBULLETSPEED 5.0
#include "Entite.hpp"

/*
const States etatsDeBullets = {
	"noTexture",
	1,
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
*/

class Bullets : public Entite {
protected:
	Entite* parent = nullptr;
public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	Bullets(int state, float directX, float directY, Entite* papa, short fact);

	virtual ~Bullets() override;
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void update();

	virtual void reactionContact(Entite* other);
};

#endif
