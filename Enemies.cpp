#include "Enemies.hpp"

uint8_t EnemyTabState[3][3][2] = { // Représente l'état et le flip en fonction de la direction dans laquelle on pousse
	{{1,0}, {3,0}, {2,0}},
	{{1,0}, {0,0}, {2,0}},
	{{1,0}, {0,0}, {2,0}}
};

/* CONSTRUCTEURS ET DESTRUCTEURS */
Enemies::Enemies() {
    Sprite::stockeur->addEnemies(this);
    hitBoxType(1, 0);
}

Enemies::Enemies(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE]) : Entite(sName, nbE, nbFPE) {
    Sprite::stockeur->addEnemies(this);
    hitBoxType(1, 0);
}

Enemies::~Enemies() {
    Sprite::stockeur->removeEnemies(this);
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */


void Enemies::update() {
    if (Sprite::stockeur->printEverything) std::cout << "Enemies::update() : " << this << std::endl;
    Vector2D v = deplacementBehaviour();
		v.normeToV(1.99);
		int x = v.x, y = v.y;
		int newEtat = EnemyTabState[y+1][x+1][0];
		if (newEtat != etat) {setEtat(newEtat);}
    attackBehaviour();
}
