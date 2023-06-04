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





// Fonctions de sauvegarde de l'objet
std::string Enemies::serialize(std::string& toWrite) {
	Entite::serialize(toWrite);
	// On n'enregistre que les paramètres nécessaires. Certains constructeur renseignent déjà les autres 
    // Ces paramètres nécessaires sont en fait les paramètres contextuels (susceptibles de changer à chaque instant)
	std::ostringstream oss;
    oss << items.size() << "|"; // On écrit la taille de la liste
    for (unsigned int i=0; i<items.size(); i++) {
        oss << items[i] << "|";
    }
    oss << taux.size() << "|";
    for (unsigned int i=0; i<taux.size(); i++) {
        oss << taux[i] << "|";
    }
    oss << invicibilityTimeStart << "|" << currentlyTakingDmg << "|";
    toWrite += oss.str();
    return "Enemies";
}

std::istringstream& Enemies::deSerialize(std::istringstream& iss) {
    Entite::deSerialize(iss);
    std::string token;
    unsigned int itemsSize=0, tauxSize=0;
    if (std::getline(iss, token, '|')) {
        itemsSize = std::stoi(token);
    }
    items.resize(itemsSize);
    for (unsigned int i=0; i<itemsSize; i++) {
        if (std::getline(iss, token, '|')) {
            items[i] = stoi(token);
        }
    }

    if (std::getline(iss, token, '|')) {
        tauxSize = std::stoi(token);
    }
    taux.resize(tauxSize);
    for (unsigned int i=0; i<tauxSize; i++) {
        if (std::getline(iss, token, '|')) {
            taux[i] = stoi(token);
        }
    }
   
    if (std::getline(iss, token, '|')) {
        invicibilityTimeStart = std::strtoul(iss.str().c_str(), nullptr, 10);
    }
    if (std::getline(iss, token, '|')) {
        currentlyTakingDmg = readBool(token);
    }
	return iss;
}