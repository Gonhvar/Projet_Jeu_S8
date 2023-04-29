#ifndef ENEMIES_HPP
#define ENEMIES_HPP

#pragma once
#include "Drop.hpp"

class Enemies : public Drop {
protected:

public:
	Enemies();

	Enemies(std::string& spriteName, uint8_t nbStates, std::vector<uint8_t>& nbFPE);

	virtual void deplacementBehaviour() = 0;
	virtual void attackBehaviour() = 0;

	void update();
};

#endif