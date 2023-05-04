#include "Attacks.hpp"

Attacks::Attacks(){

}

Attacks::Attacks(Mc* j) : state(0), joueur(j){}

Attacks::~Attacks(){

}

void Attacks::update(){
    //Exemple qu'on pourait imaginer
    if(combo == "llh"){
        state = 5;
    }

    switch(state){
        case 0 :
            break;
        
        case 1 :
            break;
            
        case 5 :
            break;
        
        default :
            break;
    }
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