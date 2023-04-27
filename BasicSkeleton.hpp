#ifndef BASICSKELETON_HPP
#define BASICSKELETON_HPP

#pragma once
#include "Enemies.hpp"
#include <math.h>

class BasicSkeleton : public virtual Enemies {
protected:

public:
	BasicSkeleton(float _x, float _y);

	void deplacementBehaviour();
	void attackBehaviour();
};

#endif