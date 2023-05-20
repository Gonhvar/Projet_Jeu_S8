#ifndef MC_HPP
#define MC_HPP
#define BASICSPEED 3000.0

#include "Killable.hpp"
#include "Attacks.hpp"
#include "Joueur2.hpp"

class Attacks;

/*
States etatsDesMc = ( // Eviter de le modifier
	"Robot",
	1,
	({1, 0, 0, 0, 0, 0, 0, 0, 0, 0})
);
*/


class Mc : public Killable {
protected :
	int mouseX;
	int mouseY;
	//Multiplicateur de depForce
	float dashValue = 0;
	uint32_t startDashTime;
	bool dashOn = false;
	uint32_t cdDashTime;
	uint32_t actualDashTime;
	Attacks* attack;

	int pushForceH = 0;
	int pushForceB = 0;
	int pushForceG = 0;
	int pushForceD = 0;

public :
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	Mc();
	~Mc();
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */
	Attacks* getAttack();

	void update();
	void get_keypress();
	void doKeyDown(SDL_KeyboardEvent& event);
	void doKeyUp(SDL_KeyboardEvent& event);
	void mousePress(SDL_MouseButtonEvent& b);
};

#endif
