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

	float depForce = 1; // > 0
	float dx = 0;
	float dy = 0;

	float masse = 1; // Augmente l'inertie et l'impact sur les autres Entite
					// n'impact pas la vitesse finale de l'Entite
	float frottements = 350; // Diminue le temps de transition et la vitesse max
							// garder frottements < masse*FPS
	Vector2D speed;

	Killable* possesseur; // Si l'Entite fait partie d'un Killable alors c'est lui
	bool isRect = false; // permet de savoir si l'Entite est dans la rectList ou
	bool isCirc = false; // la circList du stockeur

public :
	/* CONSTRUCTEURS ET DESTRUCTEURS */
	Entite();
	Entite(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE], Killable* parent = nullptr); // Si on indique pas de parent, ce sera nullptr par défaut
	~Entite();
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	void autoSetHitBox();
	void hitBoxType(bool rect, bool circ); // Met dans les listes mais n'enlève pas

	int getPV();
	int getPVMax();
	void setPV(int health);
	void changePV(int change);

	void translate(Vector2D& v); // Déplace l'Entite de v
	Vector2D& move(Vector2D& v); // Normalise la force de pousse de l'Entite à depForce
	Vector2D& moveCollisionCercle(Entite* other, Vector2D& v); // Deprecated
	void moveCollisionCercle2(Entite* other, Vector2D& v); // Modifie la vitesse de this et de l'Entite en fonction de la collision circulaire
	Vector2D& moveCollisionRectangle(Entite* other, Vector2D& v); // Modifie la vitesse de this en fonction de la collision rectangulaire
	void updateSpeedWithCollisions(); // Pour toutes les autres Entite, appel moveCollisionCercle2 et moveCollisionRectangle
	void accelerateWithForce(float fx=0, float fy=0); // Ajoute l'intégrale de l'accélération durant cette frame à speed
	
	bool contact(Entite* other);

	void mort();

	float getDx();
	float getDy();
	int getAttackDmg();
};

#endif
