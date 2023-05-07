#ifndef BASICSKELETON_HPP
#define BASICSKELETON_HPP

#include "Enemies.hpp"


const States etatsDesBasicSkeleton = {
	"BasicSkeleton",
	1,
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

class BasicSkeleton : public virtual Enemies {
protected:

public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	BasicSkeleton(float _x, float _y);
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */


	void deplacementBehaviour();
	void attackBehaviour();
	void takingDamage();
};

#endif