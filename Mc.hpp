#ifndef MC_HPP
#define MC_HPP
#define BASICSPEED 2000.0

#include "Entite.hpp"
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


class Mc : public Entite {
protected :
	
	//Multiplicateur de depForce
	float dashValue = 0;

	uint32_t startDashTime;
	uint32_t actualDashTime;
	bool dashOn = false;
	
	Attacks* attack;

	int pushForceH = 0;
	int pushForceB = 0;
	int pushForceG = 0;
	int pushForceD = 0;

public :
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	Mc();
	virtual ~Mc() override;
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */
	void update();

	Attacks* getAttack();
	
	void setPushForceH(int n);
	void setPushForceB(int n);
	void setPushForceG(int n);
	void setPushForceD(int n);
	void setStartDashTime(uint32_t time);

	void setDashOn(bool n);
	
	bool getDashOn();
	float& getDashValue();
	
};

#endif
