#include "Attacks.hpp"

Attacks::Attacks(){

}

Attacks::Attacks(Mc* j) : joueur(j){
    
    _hauteur = 64;
    _largeur = 48;

    setCoord(0,0,0);
    setOnScreen(false);

    //states = &etatAttacks;
		States* newStates = new States(); // newStates est un pointeur temporaire
		newStates->spriteName = "Attacks"; // Il n'est pas const donc on peut modifier ce qu'il y a à l'adresse
		newStates->nbEtats = 1;
		newStates->nbFrameParEtat[0] = 1;
		for (int i=1; i<newStates->nbEtats; i++) {
			newStates->nbFrameParEtat[i] = 0;
		}

        stateRect.w = 32;
        stateRect.h = 32;

		states = newStates;
		addSprite();
}


void Attacks::update(int pushForceH, int pushForceB, int pushForceG, int pushForceD){
    //Direction par défaut, on pourait peut être garder en mémoire la direction précédente pour la mettre ici ?
    int directionX = 0;
    int directionY = 0;

    if(pushForceH == 1){
        directionY =-1;
    }
    else if(pushForceB == 1){
        directionY =1;
    }

    if(pushForceG == 1){
        directionX =-1;
    }
    else if(pushForceD == 1){
        directionX =1;
    }

    //Par défaut
    if(directionX==0 && directionY == 0){
        directionX=1;
    }

    //Exemple qu'on pourait imaginer
    if(combo == "llh"){
        state = 5;
    }

    updatePlayerCoord();

    //Arreter le joueur ici avec onDash

    //std::cout << "etat : " << state << std::endl;
    switch(state){
        case 0 :
            this->setOnScreen(false);
            break;
        
        case 1 :
            //std::cout << "Attaque simple" << std::endl;
            //std::cout << "directionX :" << directionX << " directionY :" << directionY << std::endl;
            this->setOnScreen(true);
            attackDamage = 5;
            range = 60;
            
            //Met à jour l'attaque
            updateHitBox(range*directionX, range*directionY);

            //Cooldown de l'attaque
            if(SDL_GetTicks() - cdAttack > 200 ){
                state = 0;
            }
            break;
        
        case 2 : 
            //std::cout << "Attaque lourde" << std::endl;

            this->setOnScreen(true);
            attackDamage = 10;
            range = 30;
            
            //Met à jour l'attaque
            updateHitBox(range*directionX, range*directionY);

            //Cooldown de l'attaque
            if(SDL_GetTicks() - cdAttack > 300 ){
                state = 0;
            }
            break;
            
        case 5 :
            std::cout << "Combo llh!" << std::endl;

            this->setOnScreen(true);
            attackDamage = 30;
            range = 60;

            //Met à jour l'attaque
            updateHitBox(range*directionX, range*directionY);

            //Cooldown de l'attaque
            if(SDL_GetTicks() - cdAttack > 100 ){
                state = 0;
                combo = "";
            }
            break;
        
        default :
            break;
    }
}

void Attacks::updatePlayerCoord(){
    playerCoord[0] = joueur->getX();
    playerCoord[1] = joueur->getY();
}

void Attacks::updateHitBox(float attackRangeX, float attackRangeY){
    hitBox[0][0] = playerCoord[0] + attackRangeX;
    hitBox[1][0] = playerCoord[0] + attackRangeX;
    hitBox[0][1] = playerCoord[1] + attackRangeY;
    hitBox[1][1] = playerCoord[1] + attackRangeY;

    _coord[0] = (hitBox[0][0] + hitBox[1][0])/2;
    _coord[1] = (hitBox[0][1] + hitBox[1][1])/2; 
}

void Attacks::updateAttack(int attack){

    if(state == 0){
        switch(attack){
            case 0 :
                //Aucune attaque
                break;

            case 1 :
                //light attaque
                //std::cout << "Light" << std::endl;
                combo += "l";
                state = 1;
                cdAttack = SDL_GetTicks();
                break;

            case 2 :
                //heavy attaque
                //std::cout << "Heavy" << std::endl;
                combo += "h";
                state = 2;
                cdAttack = SDL_GetTicks();
                break;

            default : 
                std::cout << "Erreur nb attaque non reconnue" << std::endl;
                break;
        }
    }else{
        std::cout << "Cooldown d'attaque en cours" << std::endl;
    }
}

