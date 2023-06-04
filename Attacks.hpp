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
	static const States* etatsAttacks;

	int state;
	int range;
	uint32_t startCdAttack;
	uint32_t cdAttack;
	std::string combo;

	int directionX = 0;
    int directionY = 0;

	int attackMultiplier = 1;

	float playerCoord[2];

	bool needToClearCombo;

	int pushForceH; 
	int pushForceB; 
	int pushForceG; 
	int pushForceD;

	int debug;


public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	Attacks();
	virtual ~Attacks() override {};
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */
	static void initialisation();

	void updatePlayerCoord();
	void updateHitBox(float attackRangeX, float attackRangeY);
	void updateAttack(int attack);
	void update();
	void updateDirection(int pushForceH, int pushForceB, int pushForceG, int pushForceD);

	void setAttackMultiplier(int x);

	void findCombo();
	void applyCombo();
	void findDirection(int pushForceH, int pushForceB, int pushForceG, int pushForceD);

	void reactionContact(Entite* other);

    // Fonctions de sauvegarde de l'objet
    virtual std::string serialize(std::string& toWrite);
    virtual std::istringstream& deSerialize(std::istringstream& iss);
};

#endif
