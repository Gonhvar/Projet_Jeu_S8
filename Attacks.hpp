#ifndef ATTACKS_HPP
#define ATTACKS_HPP

#include "Entite.hpp"
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
	uint32_t startCdAttack;
	uint32_t cdAttack;
	std::string combo;

	int directionX = 0;
    int directionY = 0;

	int attackMultiplier;

	float playerCoord[2];

	bool needToClearCombo;

public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	Attacks();
	virtual ~Attacks() override {};
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void updatePlayerCoord();
	void updateHitBox(float attackRangeX, float attackRangeY);
	void updateAttack(int attack);
	void update(int pushForceH, int pushForceB, int pushForceG, int pushForceD);

	void setAttackMultiplier(int x);

	void findCombo();
	void findDirection(int pushForceH, int pushForceB, int pushForceG, int pushForceD);
};

#endif
