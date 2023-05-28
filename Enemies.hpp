#ifndef ENEMIES_HPP
#define ENEMIES_HPP

#include "Drop.hpp"
#include "Killable.hpp"
#include "Mc.hpp"

class Enemies : public Killable {
protected:
	std::vector<int> items; //mettre ici les items possibles 
	std::vector<int> taux;	//mettre ici les taux de drop des items

public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	Enemies();
	Enemies(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE]);
	virtual ~Enemies() override {};
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void update();

	virtual void deplacementBehaviour() = 0;
	virtual void attackBehaviour() = 0;
	virtual void takingDamage(Entite* other) = 0;

};

#endif