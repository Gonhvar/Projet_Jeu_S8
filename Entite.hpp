#ifndef ENTITE_HPP
#define ENTITE_HPP

#include "Sprite.hpp"
#include "Vector2D.hpp"

#define HITBOX_PTS 2
#define FPS 60

class Killable;

class Entite : public Sprite {
protected :
	int PV = 1;
	int PVMax = 1;
	int attackDamage = 0;
	
	float hitBox[HITBOX_PTS][2] = {
		{0,0},
		{0,0}
	};
	float rayon = 0;
	float masse = 1;

	float vitesse = 1;
	float dx = 0;
    float dy = 0;

	Killable* possesseur; // Si l'Entite fait partie d'un Killable alors c'est lui

public :
	/* CONSTRUCTEURS ET DESTRUCTEURS */
	Entite();
	Entite(const Entite& other);
	//Entite(std::string& spriteName, Affichage& aff);
	Entite(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE], Killable* parent = nullptr); // Si on indique pas de parent, ce sera nullptr par défaut
	~Entite();
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void autoSetHitBox();

	int getPV();
	int getPVMax();
	void setPV(int health);
	void changePV(int change);

	void translate(Vector2D& v);
	Vector2D& move(Vector2D& v);
	Vector2D& moveCollisionCercle(Entite* other, Vector2D& v);
	void moveCollisionCercle2(Entite* other, Vector2D& v); // Version améliorée qui remplacera la premoère dysfonctionnelle.
	Vector2D& moveCollisionRectangle(Entite* other, Vector2D& v);
	
	bool contact(Entite* other);

	void mort();

	float getDx();
	float getDy();
	int getAttackDmg();
};

#endif