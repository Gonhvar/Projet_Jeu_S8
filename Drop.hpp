#ifndef DROP_HPP
#define DROP_HPP

#pragma once
#include "Entite.hpp"
#include <vector>

class Drop : public Entite {
protected:
	uint8_t taux = 0; // de 0/255 à 255/255
	std::vector<uint8_t> item;	// Tableau donnant les items que ce Drop peut posséder

public:
	Drop();

	virtual void mort();
};

#endif