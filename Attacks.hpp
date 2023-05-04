#ifndef ATTACKS_HPP
#define ATTACKS_HPP

#pragma once
#include "Mc.hpp"

class Mc;

class Attacks : public Entite {
protected:
	int state;
	Mc* joueur;
	std::string combo;

public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	Attacks();
	Attacks(Mc* j);
	~Attacks();
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void updateAttack(int attack);
	void update();

};

#endif