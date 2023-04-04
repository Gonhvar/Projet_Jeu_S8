#ifndef MC_HPP
#define MC_HPP

#pragma once
#include "Entite.hpp"

class Mc : public Entite {
protected :

public :
	Mc(Affichage a){
		name = "Mc";
		texture = loadTexture("Texture/robot.png");
		PV = 20;
		
		//HitBox

		a.visit(*this);
	}
};

#endif