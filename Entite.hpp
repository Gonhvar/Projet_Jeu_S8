#ifndef ENTITE_HPP
#define ENTITE_HPP

#include "Sprite.hpp"
#include "Vector2D.hpp"

#define HITBOX_PTS 2
#define FPS 60

#define MC_FACTION 0
#define MC_FRIENDLY_FACTION 1
#define MC_BULLET_FACTION 2
#define ENEMY_FACTION 3
#define ENEMY_BULLET_FACTION 4
#define MAX_FACTION 5


class Entite : public Sprite {
protected :
	int PV = 100;
	int PVMax = 100;
	int attackDamage = 0;
	
	float hitBox[HITBOX_PTS][2] = {
		{0,0},
		{0,0}
	};
	float rayon = 0;

	float depForce = 1; // > 0
	float dx = 0;
	float dy = 0;

	float masse = 100; // Augmente l'inertie et l'impact sur les autres Entite
					// n'impact pas la vitesse finale de l'Entite
	float frottements = 0; // Diminue le temps de transition et la vitesse max
							// garder frottements < masse*FPS !!!
	Vector2D speed;

	bool isRect = false; // permet de savoir si l'Entite est dans la rectList ou
	bool isCirc = false; // la circList du stockeur

	short faction = 1;  // Permet de déterminer le comportement vis-à-vis des autres Entite.
						// 0 est la faction du Mc



public :
	/* CONSTRUCTEURS ET DESTRUCTEURS */
	Entite();
	Entite(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE]);
	virtual ~Entite() override;
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

	static bool factionInteractWith[MAX_FACTION][MAX_FACTION];

	void autoSetHitBox();
	void hitBoxType(bool circ, bool rect); // Met dans les listes mais n'enlève pas

	int getPV();
	int getPVMax();
	void setPV(int health);
	void changePV(int change); // -=

	void translate(Vector2D& v); // Déplace l'Entite de v
	void autoTranslate(); // Déplace l'Entite de speed
									 // Cette fonction existe pour ne pas demander la vitesse de l'Entite pour ensuite lui rendre dans Venera
	Vector2D& move(Vector2D& v); // Normalise la force de pousse de l'Entite à depForce
	Vector2D& moveCollisionCercle(Entite* other, Vector2D& v); // Deprecated
	void moveCollisionCercle2(Entite* other); // Modifie la vitesse de this et de l'Entite en fonction de la collision circulaire
	void moveCollisionRectangle(Entite* other); // Modifie la vitesse de this en fonction de la collision rectangulaire
	void updateSpeedWithRectCollisions(); // Pour toutes les autres Entite, appel de moveCollisionRectangle
	
	bool contact(Entite* other);
	virtual void reactionContact(Entite* other);

	void mort();

	float getDx();
	float getDy();
	int getAttackDmg();

	void addForce(float fx, float fy); // Ajoute l'intégrale de l'accélération avec durant cette frame à speed
	void addForce(Vector2D& v); // Ajoute l'intégrale de l'accélération avec durant cette frame à speed
	float& getDepForce();

	short getFaction();

	void printSelf();
};

#endif
