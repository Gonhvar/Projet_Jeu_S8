#ifndef MC_HPP
#define MC_HPP
#define BASICSPEED 2000.0

#include "Entite.hpp"
#include "Attacks.hpp"
#include "Joueur2.hpp"
#include "Controle.hpp"

class Attacks;


#define NONE 0
#define RED 1
#define GREEN 2
#define BLUE 3

class Mc : public Entite, public Controle {
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
	
	int color;

public :
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	Mc();
	virtual ~Mc() override;
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */
	void update();

	Attacks* getAttack();
	bool getDashOn();
	float& getDashValue();
	Attacks* getAttacks();
	int& getColor();
	

	
	void setPushForceH(int n);
	void setPushForceB(int n);
	void setPushForceG(int n);
	void setPushForceD(int n);
	void setStartDashTime(uint32_t time);

	void setDashOn(bool n);
	

	// Inplementer l'interface Controle pour pouvoir gérer les appels de Input
	virtual void zDown();
    virtual void zUp();
    virtual void sDown();
    virtual void sUp();
    virtual void qDown();
    virtual void qUp();
    virtual void dDown();
    virtual void dUp();
    virtual void spaceDown();
    virtual void spaceUp() {}; // On met de {} quand on ne fait rien

    // Fonctions de sauvegarde de l'objet
    virtual std::string serialize(std::string& toWrite);
    virtual void deSerialize(std::string& toRead);
};

#endif
