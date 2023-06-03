#include "Attacks.hpp"


Attacks::Attacks(){
    std::cout << "new Attacks" << std::endl;
    faction = MC_FACTION;
    
    _hauteur = 64;
    _largeur = 48;

	directionX = 0;
    directionY = 0;

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

        // Pas encore de SpriteSheet pour Attack : retour au 32x32 de noTexture
        // stateRect.w = 32;
        // stateRect.h = 32;

		states = newStates;
		addSprite("Attacks");

    state = 0;
    attackMultiplier = 1;
    startCdAttack = SDL_GetTicks();
    needToClearCombo = false;
}


void Attacks::update(int pushForceH, int pushForceB, int pushForceG, int pushForceD){
    if (Sprite::stockeur->printEverything) {
        std::cout << "Attacks::update()" << std::endl;
    }
    findDirection(pushForceH, pushForceB, pushForceG, pushForceD);

    if(stockeur->getGameTime()-startCdAttack > cdAttack){
        state = 0;
        this->setOnScreen(false);
        if(needToClearCombo){
            std::cout << "Combo cleared" << std::endl; 
            combo.clear();
            needToClearCombo = false;
        }
    }
    else{
        //Bloquer le joueur ici si on veut
    }
    
    updatePlayerCoord();

    if(state != 0){
        //Met à jour l'attaque
        updateHitBox(range*directionX, range*directionY);
    }


}

void Attacks::updatePlayerCoord(){
    playerCoord[0] = stockeur->getMc()->getX();
    playerCoord[1] = stockeur->getMc()->getY();
}

void Attacks::updateHitBox(float attackRangeX, float attackRangeY){
    hitBox[0][0] = playerCoord[0] + attackRangeX;
    hitBox[1][0] = playerCoord[0] + attackRangeX;
    hitBox[0][1] = playerCoord[1] + attackRangeY;
    hitBox[1][1] = playerCoord[1] + attackRangeY;

    _coord[0] = (hitBox[0][0] + hitBox[1][0])/2;
    _coord[1] = (hitBox[0][1] + hitBox[1][1])/2; 
}

void Attacks::setAttackMultiplier(int x){
    attackMultiplier = x;
}

void Attacks::findCombo(){
    //C'est pas trés propre mais je n'ai rien de mieux avec des std::string
    //Peut etre une récursive avec les états en impair et pair ?
    if(combo == "l"){
        state = 1;
        std::cout << "Combo l!" << std::endl;
    }
    else if(combo == "h"){
        state = 2;
        std::cout << "Combo h!" << std::endl;
        needToClearCombo = true;
    }
    else if(combo == "lh"){
        state = 2;
        std::cout << "Combo lh!" << std::endl;
        needToClearCombo = true;
    }
    else if(combo == "ll"){
        state = 1;
        std::cout << "Combo ll!" << std::endl;
    }
    else if(combo == "llh"){
        state = 5;
        needToClearCombo = true;
    }
    else if(combo == "lll"){
        state = 1;
        needToClearCombo = true;
    }
}

void Attacks::applyCombo(){
    //std::cout << "etat : " << state << std::endl;
    switch(state){
        case 0 :
            this->setOnScreen(false);
            break;
        
        case 1 :
            //std::cout << "Attaque simple" << std::endl;
            //std::cout << "directionX :" << directionX << " directionY :" << directionY << std::endl;
            attackDamage = 1 * attackMultiplier;
            range = 60;
            cdAttack = 400;
            break;
        
        case 2 : 
            //std::cout << "Attaque lourde" << std::endl;
            attackDamage = 5 *attackMultiplier;
            range = 30;
            cdAttack = 600;
            break;
            
        case 5 :
            // std::cout << "Combo llh!" << std::endl;
            attackDamage = 30 * attackMultiplier;
            range = 20;
            cdAttack = 100; 
            break;
        
        default :
            break;
    }
}

void Attacks::findDirection(int pushForceH, int pushForceB, int pushForceG, int pushForceD){
    // std::cout << "directionY :" << directionY <<  std::endl;
    if(pushForceH == 1){
        directionY =-1;
    }
    else if(pushForceB == 1){
        directionY =1;
    }
    else{
        directionY =0;
    }

    if(pushForceG == 1){
        directionX =-1;
    }
    else if(pushForceD == 1){
        directionX =1;
    }
    else{
        directionX =0;
    }
}

void Attacks::updateAttack(int attack){

    if(state == 0){
        if(attack !=0){
            switch(attack){
                case 1 :
                    //light attaque
                    //std::cout << "Light" << std::endl;
                    combo += "l";
                    break;

                case 2 :
                    //heavy attaque
                    //std::cout << "Heavy" << std::endl;
                    combo += "h";
                    break;

                default : 
                    std::cout << "Erreur nb attaque non reconnue" << std::endl;
                    break;
            }
            startCdAttack = stockeur->getGameTime();
            findCombo();
            applyCombo();
            this->setOnScreen(true);
            // std::cout << "Attack combo is : "<< combo << std::endl; 
        }
    }
    else{
        std::cout << "Cooldown d'attaque en cours" << std::endl;
    }
}