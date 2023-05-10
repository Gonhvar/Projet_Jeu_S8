#ifndef JOUEUR2_HPP
#define JOUEUR2_HPP

#include "Sprite.hpp"

const States etatsDeJoueur2 = {
	"noTexture",
	1,
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

class Joueur2 : public Sprite{
protected:
	int mouseX;
	int mouseY;
	float k = -1.0;
	
public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	Joueur2();
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void update();
	
};

#endif