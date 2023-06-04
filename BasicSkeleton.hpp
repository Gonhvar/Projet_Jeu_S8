#ifndef BASICSKELETON_HPP
#define BASICSKELETON_HPP

#define BASICSKELETONSPEED 100.0

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
	BasicSkeleton();
	BasicSkeleton(float _x, float _y);
	virtual ~BasicSkeleton() override;
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */


	Vector2D deplacementBehaviour();
	void attackBehaviour();
	void takingDamage(Entite* other);

	void reactionContact(Entite* other);

    // Fonctions de sauvegarde de l'objet
    virtual std::string serialize(std::string& toWrite);
    virtual std::istringstream& deSerialize(std::istringstream& iss);
};

#endif
