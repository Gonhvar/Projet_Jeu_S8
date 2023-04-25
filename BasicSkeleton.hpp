#ifndef BASICSKELETON_HPP
#define BASICSKELETON_HPP

#pragma once
#include "Enemies.hpp"

class BasicSkeleton : public virtual Enemies {
protected:

public:
	BasicSkeleton();
	void deplacementBehaviour();
};

#endif