#ifndef ENEMIES_HPP
#define ENEMIES_HPP

#pragma once
#include "Drop.hpp"

class Enemies : public Drop {
protected:

public:
	Enemies();
	Enemies(std::string spriteName);

	virtual void deplacementBehaviour() = 0;
	virtual void attackBehaviour() = 0;
};

#endif