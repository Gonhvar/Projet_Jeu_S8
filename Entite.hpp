#pragma once
#include "Sprite.hpp"
class Entite : public Sprite {
protected :
	int PV = 1;
	float HitBox[4][2] = {
		{0,0},
		{0,0}
	};

public :
	Entite();
	Entite(const Entite& other);

	int getPV();
	void setPV(int health);
	void damage(int damage);
};