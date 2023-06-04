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
protected :
	static const States* etatsBullets;
public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	Bullets();
	Bullets(int state, float directX, float directY, Sprite* papa, short fact);

	virtual ~Bullets() override;
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */
	static void initialisation();

	void update();

	virtual void reactionContact(Entite* other);

    // Fonctions de sauvegarde de l'objet
    virtual std::string serialize(std::string& toWrite);
    virtual std::istringstream& deSerialize(std::istringstream& iss);
};

#endif
