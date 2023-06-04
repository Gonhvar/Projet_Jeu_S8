#include "Joueur2.hpp"
#include "Mc.hpp"

const States* Joueur2::etatsJoueur2;

/* CONSTRUCTEURS ET DESTRUCTEURS */
Joueur2::Joueur2(){

    // Sprite::joueur2 = this;

    _hauteur = 32;
    _largeur = 32;
    
    setCoord(stockeur->getMc()->getX(),stockeur->getMc()->getY(), 0);

    setOnScreen(true);

    states = Joueur2::etatsJoueur2;
    addSprite("Joueur2");

    stateRectIn.w = 16;
    stateRectIn.h = 16;
    stateRectIn.x = 0;
    stateRectIn.y = 0;

    stateRect.w = 16;
    stateRect.h = 16;

    // stateRect.w = 32;
    // stateRect.h = 32;
	
    //std::cout << "Creation" << std::endl;
}

Joueur2::~Joueur2() {
    std::cout << "Delete Joueur2" << std::endl;
    // for (unsigned int i=0; i<bullets.size(); i++) {
    //     delete(bullets[i]);
    // }
    stockeur->addJoueur2(nullptr);
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */

void Joueur2::initialisation() {
	States* newStates = new States(); // newStates est un pointeur temporaire
    newStates->spriteName = "Drone"; // Il n'est pas const donc on peut modifier ce qu'il y a à l'adresse
    newStates->nbEtats = 1;
    newStates->nbFrameParEtat[0] = 1;
    for (int i=1; i<newStates->nbEtats; i++) {
        newStates->nbFrameParEtat[i] = 0;
    }
	Joueur2::etatsJoueur2 = newStates;
}


void Joueur2::update(){
    if (Sprite::stockeur->printEverything) {
        std::cout << "Joueur2::update()" << std::endl;
    }
    //Mettre un effet de ressorts autour de ce point
    deplacementDynamique();
}

void Joueur2::deplacementDynamique() {
    
    vitesseActuelle[0] += k*((stockeur->getMc()->getX()+DECALAGE_J2) - _coord[0]) - frottement*vitesseActuelle[0];
    vitesseActuelle[1] += k*((stockeur->getMc()->getY()-DECALAGE_J2) - _coord[1]) - frottement*vitesseActuelle[1];

    _coord[0] += vitesseActuelle[0];
    _coord[1] += vitesseActuelle[1];
}

void Joueur2::newTir(int state, int directX, int directY){
    
    std::cout << "creation bullets" << std::endl;
    //std::cout << "Alors X : " << x - _coord[0] << " Y :" << y - _coord[0] << std::endl;
    new Bullets(0, directX-_coord[0], directY-_coord[1], this, MC_BULLET_FACTION);

    Sprite::stockeur->getAudioManager()->playSound("01");
}


// Fonctions de sauvegarde de l'objet

std::string Joueur2::serialize(std::string& toWrite) {
	std::cout << "Serialisation" << std::endl;
	Sprite::serialize(toWrite);
	// On n'enregistre que les paramètres nécessaires. Certains constructeur renseignent déjà les autres 
    // Ces paramètres nécessaires sont en fait les paramètres contextuels (susceptibles de changer à chaque instant)
	std::ostringstream oss;
    oss << k << "|" << frottement  << "|" << vitesseActuelle[0] << "|" << vitesseActuelle[1] << "|";
	std::cout << "parsed" << std::endl;
	std::cout << "oss : " << oss.str() <<std::endl; 
    toWrite += oss.str();
    return "Joueur2";
}

std::istringstream& Joueur2::deSerialize(std::istringstream& iss) {
    std::cout << "Deserializing Joueur2 : " << iss.str() << std::endl;
	// toRead = Sprite::deSerialize(toRead);
    Sprite::deSerialize(iss);
    std::cout << "Ce qu'il reste à Joueur2 : " << iss.str() << std::endl;
    // std::istringstream iss(toRead);
    std::string token;
    if (std::getline(iss, token, '|')) {
        k = std::stof(token);
        std::cout << "k : " << k << std::endl;
    }
    if (std::getline(iss, token, '|')) {
        frottement = std::stof(token);
        std::cout << "frottement : " << frottement << std::endl;
    }
    if (std::getline(iss, token, '|')) {
        vitesseActuelle[0] = std::stof(token);
        std::cout << "vitesseActuelle[0] : " << vitesseActuelle[0] << std::endl;
    }
    if (std::getline(iss, token, '|')) {
        vitesseActuelle[1] = std::stof(token);
        std::cout << "vitesseActuelle[1] : " << vitesseActuelle[1] << std::endl;
    }
    
    std::cout << "fin deSerialize : " << std::endl;
    return iss;
}