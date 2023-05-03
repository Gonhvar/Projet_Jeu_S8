#include "Attacks.hpp"

Attacks::Attacks(){

}

Attacks::Attacks(Mc* j) : state(0), joueur(j){}

Attacks::~Attacks(){
    
}

void Attacks::updateAttack(int attack){
    switch(attack){
        case 0 :
            //Aucune attaque
            break;

        case 1 :
            //light attaque
            std::cout << "Light" << std::endl;
            combo.push_back('l');
            break;

        case 2 :
            //heavy attaque
            std::cout << "Heavy" << std::endl;
            combo.push_back('h');
            break;

        default : 
            std::cout << "Erreur nb attaque non reconnue" << std::endl;
            break;
    }
}