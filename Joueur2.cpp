#include "Joueur2.hpp"
#include "Mc.hpp"

/* CONSTRUCTEURS ET DESTRUCTEURS */
Joueur2::Joueur2(){

    // Sprite::joueur2 = this;

    _hauteur = 16;
    _largeur = 16;
    
    setCoord(stockeur->getMc()->getX(),stockeur->getMc()->getY(), 0);

    setOnScreen(true);

    //states = &(etatsDeJoueur2);
		States* newStates = new States(); // newStates est un pointeur temporaire
		newStates->spriteName = "Joueur2"; // Il n'est pas const donc on peut modifier ce qu'il y a à l'adresse
		newStates->nbEtats = 1;
		newStates->nbFrameParEtat[0] = 1;
		for (int i=1; i<newStates->nbEtats; i++) {
			newStates->nbFrameParEtat[i] = 0;
		}
		states = newStates;    
        stateRect.w = 32;
        stateRect.h = 32;
	
    	addSprite();
    //std::cout << "Creation" << std::endl;
}

Joueur2::~Joueur2() {
    std::cout << "Delete Joueur2" << std::endl;
    // for (unsigned int i=0; i<bullets.size(); i++) {
    //     delete(bullets[i]);
    // }
    bullets.clear();
    stockeur->addJoueur2(nullptr);
}
/* FIN CONSTRUCTEURS ET DESTRUCTEURS */


void Joueur2::update(){
    if (Sprite::stockeur->printEverything) std::cout << "Joueur2::update()" << std::endl;
    //Mettre un effet de ressorts autour de ce point
    deplacementDynamique();

    // for(Bullets* bullet : bullets){
    //     bullet->update();
    // }
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
    bullets.push_back(new Bullets(0, directX-_coord[0], directY-_coord[1], this));
}

void Joueur2::removeBullet(Bullets* bullet) {
    auto it = std::find(bullets.begin(), bullets.end(), bullet);
    if (it != bullets.end()) {
        bullets.erase(it); 
    }
}