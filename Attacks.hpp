#ifndef ATTACKS_HPP
#define ATTACKS_HPP


#include "Mc.hpp"

class Mc;

class Attacks : public Entite {
protected:
	int state;
	Mc* joueur;
	std::string combo;
	float playerCoord[2];
	int attackDamage;

public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	Attacks();
	Attacks(Mc* j);
	~Attacks();
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void updatePlayerCoord();
	void updateHitBox(float attackRangeX, float attackRangeY);
	void updateAttack(int attack);
	void update(int directionX, int directionY);

};

#endif