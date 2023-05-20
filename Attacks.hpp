#ifndef ATTACKS_HPP
#define ATTACKS_HPP


#include "Mc.hpp"

class Mc;

/*
const States etatAttacks = {
	"attaque",
	1,
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
*/

class Attacks : public Entite {
protected:
	int state;
	int range;
	uint32_t cdAttack;
	std::string combo;

	float playerCoord[2];
	Mc* joueur;

public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	Attacks();
	Attacks(Mc* j);
	~Attacks();
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void updatePlayerCoord();
	void updateHitBox(float attackRangeX, float attackRangeY);
	void updateAttack(int attack);
	void update(int pushForceH, int pushForceB, int pushForceG, int pushForceD);

};

#endif
