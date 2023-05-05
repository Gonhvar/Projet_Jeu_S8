#include "Attacks.hpp"

Attacks::Attacks(){

}

Attacks::Attacks(Mc* j) : state(0), joueur(j){
    
}

Attacks::~Attacks(){

}

void Attacks::update(int directionX, int directionY){
    //En vrai il faudrait mettre la norme
    //Si pas de direction 
    if(directionX == 0){
        directionX=1;
    }
    if(directionY == 0){
        directionY=1;
    }
    //Exemple qu'on pourait imaginer
    if(combo == "llh"){
        state = 5;
    }

    updatePlayerCoord();

    switch(state){
        case 0 :
            break;
        
        case 1 :
            attackDamage = 5;
            updateHitBox(40*directionX, 40*directionY);
            break;
        
        case 2 : 
            break;
            
        case 5 :
            
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
}

void Attacks::updateAttack(int attack){
    switch(attack){
        case 0 :
            //Aucune attaque
            break;

        case 1 :
            //light attaque
            std::cout << "Light" << std::endl;
            combo += "l";
            break;

        case 2 :
            //heavy attaque
            std::cout << "Heavy" << std::endl;
            combo += "h";
            break;

        default : 
            std::cout << "Erreur nb attaque non reconnue" << std::endl;
            break;
    }
}