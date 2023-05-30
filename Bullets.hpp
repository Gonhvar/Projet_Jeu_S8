#ifndef BULLETS_HPP
#define BULLETS_HPP

#pragma once
#define BASICBULLETSPEED 100.0
#include "Entite.hpp"

class Joueur2;


/*
const States etatsDeBullets = {
	"noTexture",
	1,
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
*/

class Bullets : public Entite {
protected:
	Joueur2* parent = nullptr; // Il faudra probablement remplacer ça par un Entite*
public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	Bullets(int state, float x, float y, Joueur2* papa, short fact);

	virtual ~Bullets() override;
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void update();

	virtual void reactionContact(Entite* other);
};

#endif
