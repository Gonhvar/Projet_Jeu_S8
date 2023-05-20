#ifndef KILLABLE_HPP
#define KILLABLE_HPP

#include "Entite.hpp"

class Killable : public Entite {
    // a priori c'est une classe virtuelle pure
    // Parce qu'il n'y a pas littérallement de Killable.
    // Il y a des mobs spécifiques qui sont des Killable, le Mc aussi

    // Killable hérite d'Entite car il y a beaucoup de paramètres et de fonctions similaires dans Entite et Killable
    // A priori, un Killable a toujours une Entite donc autant faire en sorte que c'en soit une.
    // Si on veut qu'un Killable contienne plus d'Entite on les rajoute dans le tableau entite.

protected :
    std::vector<Entite*> entite; // Maximum 255 entite
    uint32_t invicibilityTimeStart;
	bool currentlyTakingDmg = false;

public :
    /* CONSTRUCTEURS ET DESTRUCTEURS */
    Killable();
    Killable(std::string sName, uint8_t nbE, uint8_t nbFPE[MAX_FPE]);
    ~Killable();
	/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

    void update();
    
    void translate(Vector2D& v);
    void updateSpeedWithCollisions(); // Redéfinition de cette fonction pour toutes les hitbox du killable


	virtual void mort();
};

#endif