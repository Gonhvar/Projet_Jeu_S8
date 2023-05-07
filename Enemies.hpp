#ifndef ENEMIES_HPP
#define ENEMIES_HPP

#include "Drop.hpp"

class Enemies : public Drop {
protected:

public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	Enemies() = default;
	Enemies(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE]);
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void update();

	virtual void deplacementBehaviour() = 0;
	virtual void attackBehaviour() = 0;

};

#endif