#ifndef SKELETONSHOOTER_HPP
#define SKELETONSHOOTER_HPP

#define BASICSKELETONSHOOTERSPEED 5.0

#include "Enemies.hpp"

class SkeletonShooter : public virtual Enemies {
protected:
	static const States* etatsSkeletonShooter;

	float knockback = 3.0;
	uint32_t cooldown = 1000;
	uint32_t startShooting;

public:
    /* CONSTRUCTEURS ET DESTRUCTEURS */
	SkeletonShooter();
	SkeletonShooter(float _x, float _y);
	virtual ~SkeletonShooter() override;
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */
	static void initialisation();


	Vector2D deplacementBehaviour();
	void attackBehaviour();
	void takingDamage(Entite* other);

	void reactionContact(Entite* other);

    // Fonctions de sauvegarde de l'objet
    virtual std::string serialize(std::string& toWrite);
    virtual std::istringstream& deSerialize(std::istringstream& iss);
};

#endif
