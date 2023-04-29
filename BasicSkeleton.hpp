#ifndef BASICSKELETON_HPP
#define BASICSKELETON_HPP

#pragma once
#include "Enemies.hpp"
#include <math.h>

const States etatsDesBasicSkeleton = {
	"BasicSkeleton",
	1,
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

class BasicSkeleton : public virtual Enemies {
protected:

public:
	BasicSkeleton(float _x, float _y);

	static void Initialisation();
	
	void deplacementBehaviour();
	void attackBehaviour();
};

#endif