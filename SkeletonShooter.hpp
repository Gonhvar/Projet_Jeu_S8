#ifndef SKELETONSHOOTER_HPP
#define SKELETONSHOOTER_HPP

#define BASICSKELETONSHOOTERSPEED 5.0

#include "Enemies.hpp"

class SkeletonShooter : public virtual Enemies {
protected:
	
	float knockback = 3.0;
	uint32_t cooldown = 1000;
	uint32_t startShooting;

public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	SkeletonShooter(float _x, float _y);
	virtual ~SkeletonShooter() override;
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */


	Vector2D deplacementBehaviour();
	void attackBehaviour();
	void takingDamage(Entite* other);

	void reactionContact(Entite* other);
};

#endif
