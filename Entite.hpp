#ifndef ENTITE_HPP
#define ENTITE_HPP

#pragma once
#include "Sprite.hpp"

#define HITBOX_PTS 2
#define FPS 60

class Killable;

class Entite : public Sprite {
protected :
	int PV = 1;
	int PVMax = 1;
	
	float hitBox[HITBOX_PTS][2] = {
		{0,0},
		{0,0}
	};
	float vitesse = 1;
	float dx = 0;
    float dy = 0;

	Killable* possesseur; // Si l'Entite fait partie d'un Killable alors c'est lui

public :
	/* CONSTRUCTEURS ET DESTRUCTEURS */
	Entite() = default;
	Entite(const Entite& other);
	//Entite(std::string& spriteName, Affichage& aff);
	Entite(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE], Killable* parent = nullptr); // Si on indique pas de parent, ce sera nullptr par défaut
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void autoSetHitBox();

	int getPV();
	int getPVMax();
	void setPV(int health);
	void changePV(int change);

	void translate(float dx, float dy);
	void move(float moveX, float moveY);
	bool contact(Entite* other);

	virtual void mort();

	float getDx();
	float getDy();

	static std::vector<Entite*> allEntities;
};

#endif