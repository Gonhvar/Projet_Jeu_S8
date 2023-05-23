#ifndef BASICSKELETON_HPP
#define BASICSKELETON_HPP

#define BASICSKELETONSPEED 300.0

#include "Enemies.hpp"

/*
const States etatsDesBasicSkeleton = {
	"BasicSkeleton",
	1,
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
*/

class BasicSkeleton : public virtual Enemies {
protected:
	float knockback = 3.0;

public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	BasicSkeleton(float _x, float _y);
	virtual ~BasicSkeleton() override {};
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */


	void deplacementBehaviour();
	void attackBehaviour();
	void takingDamage(Entite* other);

	void reactionContact(Entite* other);
};

#endif
