#ifndef ENEMIES_HPP
#define ENEMIES_HPP

#include "Drop.hpp"
#include "Mc.hpp"

class Enemies : public Entite {
protected:
	std::vector<int> items; //mettre ici les items possibles 
	std::vector<int> taux;	//mettre ici les taux de drop des items
    uint32_t invicibilityTimeStart;
	bool currentlyTakingDmg = false;

public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	Enemies();
	Enemies(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE]);
	virtual ~Enemies() override;
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void update();

	virtual Vector2D deplacementBehaviour() = 0;
	virtual void attackBehaviour() = 0;
	virtual void takingDamage(Entite* other) = 0;

    // Fonctions de sauvegarde de l'objet
    virtual std::string serialize(std::string& toWrite);
    virtual std::istringstream& deSerialize(std::istringstream& iss);
};

#endif
